#include "Framework.h"
#include "IntegratedRect.h"
#include "Game/Transform.h"
#include "ShaderBuffers/AlphaBuffer.h"
#include "ShaderBuffers/ColorBuffer.h"
#include "Effects/Dissolve.h"
#include "Utilities/ShaderCreator.h"
#include "Renders/Shaders/IShader.h"


IntegratedRect::IntegratedRect(Transform * transform)
	: transform(transform)
{
	//vertices

	{

		vertices.assign(4, VertexTexture());



		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // left bottom

		vertices[0].uv = Vector2(0, 1);



		vertices[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); // left top

		vertices[1].uv = Vector2(0, 0);



		vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); // right bottom

		vertices[2].uv = Vector2(1, 1);



		vertices[3].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); // right top

		vertices[3].uv = Vector2(1, 0);
	}



	//vertexBuffer

	{
		vb = new VertexBuffer();

		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}



	//indexBuffer

	{

		indices = { 0, 1, 2, 2, 1, 3 };



		ib = new IndexBuffer();

		ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	}



	//vertexShader

	{

		//vs = new VertexShader();

		//vs->Create(ShaderPath + L"IntegratedShader.hlsl", "VS");
		ShaderCreator::Create<VertexShader>((IShader**)&vs, ShaderPath + L"IntegratedShader.hlsl", "VS");
	}



	//inputLayout

	{

		il = new InputLayout();

		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());

	}



	//pixelShader

	{

		/*ps = new PixelShader();

		ps->Create(ShaderPath + L"IntegratedShader.hlsl", "PS");*/

		ShaderCreator::Create<PixelShader>((IShader**)&ps, ShaderPath + L"IntegratedShader.hlsl", "PS");

	}
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	HRESULT hr = DEVICE->CreateBlendState(&blendDesc, &blendState);
	CHECK(hr);

	wb = new WorldBuffer();

	edge = new RectEdge();
	box = new BoundingBox(edge);


	dissolveBuffer = new DissolveBuffer();
	colorBuffer = new ColorBuffer();
	colorBuffer->SetColor(Color(0, 0, 0, 0));
	alphaBuffer = new AlphaBuffer();
	alphaBuffer->SetAlpha(1);
	Texture2D * map = new Texture2D(TexturePath + L"dissolveMap.jpg");
	dissolveMap = map->GetSRV();
	SAFE_DELETE(map);
}



IntegratedRect::~IntegratedRect()

{

	SAFE_DELETE(wb);



	//SAFE_DELETE(ps);



	SAFE_DELETE(il);



	//SAFE_DELETE(vs);



	SAFE_DELETE(ib);

	SAFE_DELETE(vb);

}

void IntegratedRect::SetShader(wstring shaderPath)
{
	//vs->Clear();
	//ps->Clear();

	ShaderCreator::Create<VertexShader>((IShader**)&vs, shaderPath, "VS");
	ShaderCreator::Create<PixelShader>((IShader**)&ps, shaderPath, "PS");

}

void IntegratedRect::Update()

{

	UpdateWorld();
}



void IntegratedRect::Render()
{
		DC->PSSetShaderResources(1, 1, &dissolveMap);
		dissolveBuffer->SetPSBuffer(4);
		alphaBuffer->SetPSBuffer(2);
		colorBuffer->SetPSBuffer(3);

	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();

	wb->SetVSBuffer(0); // set constant buffer (transform buffer)

	ps->SetShader();
	if (srv != nullptr)
		DC->PSSetShaderResources(0, 1, &srv);

	DC->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
	DC->DrawIndexed(ib->GetCount(), 0, 0);

}


string IntegratedRect::MakeLabel(string preFix)
{
	string label = preFix + "##" + to_string((uint)this);
	return label;
}

void IntegratedRect::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void IntegratedRect::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}


void IntegratedRect::UpdateWorld()
{
	D3DXMatrixTranslation(&T, transform->position.x, transform->position.y, transform->position.z);
	D3DXMatrixScaling(&S, transform->size.x, transform->size.y, transform->size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(transform->rotation));
	world = S * R *  T;

	wb->SetWorld(world);

}