//#include "Framework.h"
//#include "Drone.h"
//#include "Game/Transform.h"
//
//Drone::Drone(short id ,Vector3 position, Vector3 size, float rotation)
//	: Boid(id)
//{
//
//	//vertices
//
//	{
//
//		vertices.assign(4, VertexTexture());
//
//
//
//		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f); // left bottom
//
//		vertices[0].uv = Vector2(0, 1);
//
//
//
//		vertices[1].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f); // left top
//
//		vertices[1].uv = Vector2(0, 0);
//
//
//
//		vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f); // right bottom
//
//		vertices[2].uv = Vector2(1, 1);
//
//
//
//		vertices[3].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f); // right top
//
//		vertices[3].uv = Vector2(1, 0);
//	}
//
//
//
//	//vertexBuffer
//
//	{
//		vb = new VertexBuffer();
//
//		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
//	}
//
//
//
//	//indexBuffer
//
//	{
//		indices = { 0, 1, 2, 2, 1, 3 };
//
//
//
//		ib = new IndexBuffer();
//
//		ib->Create(indices, D3D11_USAGE_IMMUTABLE);
//
//	}
//
//
//
//	//vertexShader
//
//	{
//
//		vs = new VertexShader();
//
//		vs->Create(ShaderPath + L"VertexTexture.hlsl", "VS");
//	}
//
//
//
//	//inputLayout
//
//	{
//
//		il = new InputLayout();
//
//		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());
//
//	}
//
//
//
//	//pixelShader
//
//	{
//
//		ps = new PixelShader();
//
//		ps->Create(ShaderPath + L"VertexTexture.hlsl", "PS");
//
//	}
//	D3D11_BLEND_DESC blendDesc;
//	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
//
//	blendDesc.IndependentBlendEnable = false;
//
//	blendDesc.RenderTarget[0].BlendEnable = true;
//	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
//	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
//	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
//	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
//	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
//	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
//	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//	HRESULT hr = DEVICE->CreateBlendState(&blendDesc, &blendState);
//	CHECK(hr);
//
//	wb = new WorldBuffer();
//
//	transform = new Transform();
//	transform->position = position;
//	transform->size = size;
//	transform->rotation = rotation;
//
//	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Drone.png");
//	SetSRV(tex->GetSRV());
//	SAFE_DELETE(tex);
//
//}
//
//Drone::~Drone()
//{
//
//
//	SAFE_DELETE(wb);
//
//
//
//	SAFE_DELETE(ps);
//
//
//
//	SAFE_DELETE(il);
//
//
//
//	SAFE_DELETE(vs);
//
//
//
//	SAFE_DELETE(ib);
//
//	SAFE_DELETE(vb);
//}
//
//void Drone::SetShader(wstring shaderPath)
//{
//	vs->Clear();
//	ps->Clear();
//
//	vs->Create(shaderPath, "VS");
//	ps->Create(shaderPath, "PS");
//}
//
//void Drone::Update()
//{
//	UpdateWorld();
//}
//
//void Drone::UpdateWorld()
//{
//	D3DXMATRIX velocity;
//	//D3DXMatrixTranslation(&velocity, transform->velocity.x, transform->velocity.y, transform->velocity.z);
//	cout << this->GetPos()->x << " : " << this->GetPos()->y << endl;
//	D3DXMatrixTranslation(&T, this->GetPos()->x, this->GetPos()->y, 0);
//	D3DXMatrixScaling(&S, transform->size.x, transform->size.y, transform->size.z);
//	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(this->GetOrient()->z));
//	world = S * R *  T;
////	world = velocity * Time::Delta() * world;
//
//	wb->SetWorld(world);
//}
//
//void Drone::Render()
//{
//	vb->SetIA();
//	ib->SetIA();
//	il->SetIA();
//	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	vs->SetShader();
//
//	wb->SetVSBuffer(0); // set constant buffer (transform buffer)
//
//	ps->SetShader();
//	if (srv != nullptr)
//		DC->PSSetShaderResources(0, 1, &srv);
//
//	DC->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
//	DC->DrawIndexed(ib->GetCount(), 0, 0);
//}
