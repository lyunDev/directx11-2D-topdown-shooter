#include "Framework.h"
#include "Dissolve.h"
#include "Game/Transform.h"

Dissolve::Dissolve(Transform * transform)
	: TextureRect(transform)
{

	Texture2D * dissolveMap = new Texture2D(TexturePath + L"dissolveMap.jpg");
	SetDissolveMap(dissolveMap->GetSRV());
	SAFE_DELETE(dissolveMap);

	SetShader(ShaderPath + L"Dissolve.hlsl");
	dissolveBuffer = new DissolveBuffer();
}

Dissolve::~Dissolve()
{
	SAFE_DELETE(wb);



	SAFE_DELETE(ps);



	SAFE_DELETE(il);



	SAFE_DELETE(vs);



	SAFE_DELETE(ib);

	SAFE_DELETE(vb);
}

void Dissolve::Update()
{
	TextureRect::Update();
	//D3DXMATRIX velocity;
	//D3DXMatrixTranslation(&velocity, transform->velocity.x, transform->velocity.y, transform->velocity.z);
	////D3DXMatrixTranslation(&T, transform->position.x, transform->position.y, transform->position.z);
	//D3DXMatrixTranslation(&T, WinMaxWidth/ 2, WinMaxHeight /2, 0);
	//D3DXMatrixScaling(&S, WinMaxWidth, WinMaxHeight,1);
	////D3DXMatrixScaling(&S, transform->size.x, transform->size.y, transform->size.z);
	//D3DXMatrixRotationZ(&R, (float)D3DXToRadian(transform->rotation));
	//world = S * R *  T;
	//world = velocity * Time::Delta() * world;

	//wb->SetWorld(world);
}



void Dissolve::Render()
{

	//if (texture != nullptr)
	//	DC->PSSetShaderResources(0, 1, &texture);
	if (dissolveMap != nullptr)
		DC->PSSetShaderResources(1, 1, &dissolveMap);


	dissolveBuffer->SetPSBuffer(2);


	TextureRect::Render();
}
