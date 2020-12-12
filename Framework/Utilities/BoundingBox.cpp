#include "Framework.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox(RectEdge* rect)
	: rect(rect)
{

}

BoundingBox::~BoundingBox()
{
	SAFE_RELEASE(blend[0]);
	SAFE_RELEASE(blend[1]);

	SAFE_DELETE(WB);
	SAFE_DELETE(CB);

	SAFE_DELETE(IL);

	SAFE_DELETE(VS);
	SAFE_DELETE(PS);

	SAFE_DELETE(IB);
	SAFE_DELETE(VB);
}

void BoundingBox::Init()
{
	vertices.assign(4, VertexColor());

	vertices.assign(4, VertexColor());
	vertices[0].position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].position = Vector3(0.0f, rect->LT.y - rect->RB.y, 0.0f);
	vertices[2].position = Vector3(rect->RB.x - rect->LT.x, 0.0f, 0.0f);
	vertices[3].position = Vector3(rect->RB.x - rect->LT.x, rect->LT.y - rect->RB.y, 0.0f);

	for (VertexColor& v : vertices)
		v.color = D3DXCOLOR(0, 1.0f, 0, 0.3f);

	VB = new VertexBuffer();
	VB->Create(vertices, D3D11_USAGE_DYNAMIC);

	indices.resize(8, UINT());
	indices = { 0, 1, 1, 3, 3, 2, 2, 0 };

	IB = new IndexBuffer();
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	VS = new VertexShader();
	VS->Create(ShaderPath + L"CollisionShader.hlsl", "VS");

	PS = new PixelShader();
	PS->Create(ShaderPath + L"CollisionShader.hlsl", "PS");

	IL = new InputLayout();
	IL->Create(VertexColor::descs, VertexColor::count, VS->GetBlob());

	WB = new WorldBuffer();
	CB = new CollisionBuffer();

	{
		D3D11_BLEND_DESC desc;
		States::GetBlendDesc(&desc);
		States::CreateBlend(&desc, &blend[0]);

		desc.RenderTarget[0].BlendEnable = true;
		States::CreateBlend(&desc, &blend[1]);
	}
}

void BoundingBox::Update()
{
	D3DXMatrixTranslation(&world, rect->LT.x, rect->RB.y, 0.0f);
	WB->SetWorld(world);
}

void BoundingBox::Render()
{
	VB->SetIA();
	IB->SetIA();
	IL->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	VS->SetShader();
	PS->SetShader();

	WB->SetVSBuffer(0);
	CB->SetPSBuffer(0);

	DC->OMSetBlendState(blend[1], nullptr, 0xffffffff);
	DC->DrawIndexed(IB->GetCount(), 0, 0);
	DC->OMSetBlendState(blend[0], nullptr, 0xffffffff);
}

function<void()> BoundingBox::GetFuncPtr()
{
	return bind(&CollisionBuffer::SwitchRender, CB);
}

bool BoundingBox::AABB(BoundingBox * a, BoundingBox * b)
{
	if (a == nullptr || b == nullptr) return false;

	RectEdge aRect = *a->rect;
	RectEdge bRect = *b->rect;

	if (aRect.RB.x >= bRect.LT.x
		&& aRect.LT.x <= bRect.RB.x
		&& aRect.LT.y >= bRect.RB.y
		&& aRect.RB.y <= bRect.LT.y
		)
		return true;
	else
		return false;
}

bool BoundingBox::CheckOutside()
{
	if (rect->LT.x <= 0
		|| rect->RB.x >= WinMaxWidth
		|| rect->LT.y <= 0
		|| rect->RB.y >= WinMaxHeight)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////


OBB::OBB(TransformData * transform)
	: transform(transform)
{
}

OBB::~OBB()
{
}

// 중심 축 잡기
// rect의 기준 축이 좌측 아래로 잡혀있기 때문에
// 센터 좌표를 구해야한다.
void OBB::Calculation()
{
	RectEdge r = (*transform).edge;
	centerPos.x = (r.RB.x + r.LT.x) * 0.5f;
	centerPos.y = (r.RB.y + r.LT.y) * 0.5f;
	centerPos.z = 0.0f;

	Vector3 position = (*transform).position;
	centerW = (r.RB - position) * 0.5f;
	centerW.z = 0.0f;

	centerH = (r.LT - position) * 0.5f;
	centerH.z = 0.0f;
}

bool OBB::CheckIntersect(OBB * a, OBB * b)
{

	TransformData* transA = a->transform;
	TransformData* transB = b->transform;

	Vector3 dist = b->centerPos - a->centerPos;

	// rect의 x축과 y축을 보관한다.
	// calculation에서 구해야함
	vector<Vector3> vecs;
	vecs.push_back(a->centerH);
	vecs.push_back(a->centerW);
	vecs.push_back(b->centerH);
	vecs.push_back(b->centerW);

	// 분리축을 구한다.
	// rotation값에 cos, sin값을 곱해 기울어진 단위 벡터를 구한다.
	vector<Vector3> separatedAxises;
	separatedAxises.push_back(Vector3(cosf(D3DXToRadian(transA->rotation)), sinf(D3DXToRadian(transA->rotation)), 0.0f));
	separatedAxises.push_back(Vector3(cosf(D3DXToRadian(transA->rotation + 90.0f)), sinf(D3DXToRadian(transA->rotation + 90.0f)), 0.0f));
	separatedAxises.push_back(Vector3(cosf(D3DXToRadian(transB->rotation)), sinf(D3DXToRadian(transB->rotation)), 0.0f));
	separatedAxises.push_back(Vector3(cosf(D3DXToRadian(transB->rotation + 90.0f)), sinf(D3DXToRadian(transB->rotation + 90.0f)), 0.0f));

	float sum = 0;
	for (int i = 0; i < separatedAxises.size(); i++)
	{
		sum = 0;
		for (int j = 0; j < vecs.size(); j++)
			// 분리축과 각 벡터의 x, y축의 내적(정사영)을 모두 합한다. 
			sum += abs(D3DXVec3Dot(&separatedAxises[i], &vecs[j]));

		// 모두 합한 값이 두 rect사이의 벡터의 내적(정사영)보다 하나라도 작다면 충돌하지 않은 것
		if (abs(D3DXVec3Dot(&dist, &separatedAxises[i])) > sum)
			return false;
	}

	return true;
}
