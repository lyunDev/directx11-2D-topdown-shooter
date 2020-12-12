#include "Framework.h"
#include "CollisionBox.h"

#include "Geometries/Rect.h"
#include "Game/Transform.h"

#include "Utilities/ShaderCreator.h"

CollisionBox::CollisionBox(Vector3 * position, Vector3 * scale, float * rotation)
	: position(position), scale(scale), rotation(rotation)
{
#ifdef COLLISION_RENDER

	vertices.assign(4, VertexTexture());
	vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);

	vertices[0].uv = Vector2(0, 1);



	vertices[1].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	vertices[1].uv = Vector2(1, 0);



	vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);

	vertices[2].uv = Vector2(1, 1);



	vertices[3].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);

	vertices[3].uv = Vector2(0, 0);

	{
		vb = new VertexBuffer();

		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}

	{

		indices = { 0, 1, 2, 0, 3, 1 };



		ib = new IndexBuffer();

		ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	}

	{

		//vs = new VertexShader();

		//vs->Create(ShaderPath + L"Collision.hlsl", "VS");
		ShaderCreator::Create<VertexShader>((IShader**)&vs, ShaderPath + L"Collision.hlsl", "VS");
	}

	{

		il = new InputLayout();

		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());

	}
	{

		//ps = new PixelShader();

		//ps->Create(ShaderPath + L"Collision.hlsl", "PS");
		ShaderCreator::Create<PixelShader>((IShader**)&ps, ShaderPath + L"Collision.hlsl", "PS");
	}

	wb = new WorldBuffer();

#endif
}

CollisionBox::~CollisionBox()
{
}

bool CollisionBox::OBB(CollisionBox*other)
{
	//// rect간의 거리를 구한다.
	//Vector3 dist = *position - other->GetPosition();
	//
	//// 각 rect의 분리축을 구한다.
	//Vector3 vec[4] = { GetHeightVector(*this), GetHeightVector(*other),
	//				   GetWidthVector(*this), GetWidthVector(*other) };
	//Vector3 unit;
	//// 모든 분리축에서 계산을 한다.
	//for (int i = 0; i < 4; i++)
	//{
	//	double sum = 0;
	//	double sum2 = 0;
	//	// 분리축은 오로지 방향만 갖기 때문에
	//	// 정규화해준다.
	//	//unit = GetUnitVector(vec[i]); 
	//	D3DXVec3Normalize(&unit, &vec[i]);
	//	for (int j = 0; j < 4; j++)
	//	{
	//		// 각 rect의 모든 축에서 분리축에 대한 정사영을 구한 후 합한다.
	//		// 이 과정에서 각 rect의 x축과 y축이 더해져 분리축 기준으로 
	//		// 가장 많은 면적을 차지하는 정사영을 구하게 되고
	//		// 두 rect의 가장 큰 면적을 차지하는 정사영을 더하는 것과 같은 값이 된다.
	//		//sum += abs(vec[j].x * unit.x + vec[j].y * unit.y);
	//		sum += abs(D3DXVec3Dot(&vec[j], &unit));
	//	}
	//	// rect간의 거리를 내적한 결과보다 sum이 크다면 충돌한 것
	//	if (abs(D3DXVec3Dot(&dist, &unit)) > sum)
	//	{
	//		return false;
	//	}
	//	/*if (abs(dist.x * unit.x + dist.y * unit.y) > sum)
	//	{
	//		return false;
	//	}*/
	//}
	//return true;


	{
		Vector3 dist = other->GetPosition() - *position;

		vector<Vector3> vecs;
		vecs.push_back(GetHeightVector(*this));
		vecs.push_back(GetWidthVector(*this));
		vecs.push_back(GetHeightVector(*other));
		vecs.push_back(GetWidthVector(*other));

		vector<Vector3> separatedAxises;
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(*rotation)), sinf(D3DXToRadian(*rotation)), 0.0f));
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(*rotation + 90.0f)), sinf(D3DXToRadian(*rotation + 90.0f)), 0.0f));
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(other->GetRotation())), sinf(D3DXToRadian(other->GetRotation())), 0.0f));
		separatedAxises.push_back(Vector3(cosf(D3DXToRadian(other->GetRotation() + 90.0f)), sinf(D3DXToRadian(other->GetRotation() + 90.0f)), 0.0f));

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
}

bool CollisionBox::OBB(CollisionBox * box1, CollisionBox * box2)
{
	Vector3 dist = box1->GetPosition() - box2->GetPosition();

	Vector3 vec[4] = { GetHeightVector(*box1), GetHeightVector(*box2),
					   GetWidthVector(*box1), GetWidthVector(*box2) };
	Vector3 unit;

	for (int i = 0; i < 4; i++)
	{
		double sum = 0;
		double sum2 = 0;
		D3DXVec3Normalize(&unit, &vec[i]);
		for (int j = 0; j < 4; j++)
		{
			sum += abs(D3DXVec3Dot(&vec[j], &unit));
		}
		if (abs(D3DXVec3Dot(&dist, &unit)) > sum)
		{
			return false;
		}
	}
	return true;
}

void CollisionBox::Update()
{
#ifdef COLLISION_RENDER
	D3DXMatrixTranslation(&T, position->x, position->y, position->z);
	D3DXMatrixScaling(&S, scale->x, scale->y, scale->z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(*rotation));
	world = S * R * T;
	wb->SetWorld(world);
#endif
}

void CollisionBox::Render()
{
#ifdef COLLISION_RENDER
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	vs->SetShader();
	wb->SetVSBuffer(0);
	ps->SetShader();
	DC->DrawIndexed(ib->GetCount(), 0, 0);
#endif
}

const Vector3& CollisionBox::GetPosition() const
{
	return *position;
}

const Vector3& CollisionBox::GetScale() const
{
	return *scale;
}

const float& CollisionBox::GetRotation() const
{
	return *rotation;
}

void CollisionBox::SetTransform(Vector3 * position, Vector3 * scale, float * rotation)
{
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

bool CollisionBox::IsStaying(CollisionBox * other)
{
	for (auto collision : stayingColliders)
	{
		if (other == collision)
		{
			return true;
		}
	}
	return false;
}

void CollisionBox::PushStayedCollider(CollisionBox * other)
{
	stayingColliders.push_back(other);
}

void CollisionBox::PopStayedCollider(CollisionBox * other)
{
	stayingColliders.remove(other);
}


Vector3 CollisionBox::GetHeightVector(const CollisionBox collisionBox)
{
	/*Vector3 ret;
	ret.x = collisionBox.GetScale().y * sinf((float)D3DXToRadian(collisionBox.GetRotation())) / 2;
	ret.y = -collisionBox.GetScale().y * cosf((float)D3DXToRadian(collisionBox.GetRotation())) / 2;
	ret.z = 0;*/

	Vector3 ret2;
	Transform tr;
	tr.position = Vector3(0, 0, 0);
	tr.position.y += collisionBox.scale->y * 0.5f;
	//tr.position.y += collisionBox.scale->y * 0.5f;
	tr.Rotate((float)D3DXToRadian(collisionBox.GetRotation()));
	tr.position += *collisionBox.position;
	ret2 = tr.position - *collisionBox.position;
	ret2.z = 0.0f;
	return ret2;
}

Vector3 CollisionBox::GetWidthVector(CollisionBox collisionBox)
{
	/*Vector3 ret;
	ret.x = collisionBox.GetScale().x * cosf((float)D3DXToRadian(collisionBox.GetRotation())) / 2;
	ret.y = -collisionBox.GetScale().x * sinf((float)D3DXToRadian(collisionBox.GetRotation())) / 2;
	ret.z = 0;*/

	Vector3 ret2;
	Transform tr;
	//tr.position = *collisionBox.position;
	tr.position = Vector3(0, 0, 0);
	tr.position.x += collisionBox.scale->x * 0.5f;
	tr.Rotate((float)D3DXToRadian(collisionBox.GetRotation()));
	tr.position += *collisionBox.position;
	ret2 = tr.position - *collisionBox.position;
	ret2.z = 0;

	return ret2;
}

Vector3 CollisionBox::GetUnitVector(Vector3 vec) // 내적
{
	Vector3 ret;
	float size;
	size = sqrt(vec.x * vec.x + vec.y * vec.y);
	ret.x = vec.x / size;
	ret.y = vec.y / size;
	return ret;
}
