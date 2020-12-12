#include "Framework.h"
#include "NormalBlur.h"
#include "Game/Transform.h"

NormalBlur::NormalBlur(Transform * transform)
	: TextureRect(transform)
{
	buffer = new BlurBuffer();
	buffer->SetTextureSize({ this->transform->size.x, this->transform->size.y });
	buffer->SetBlurCount(3);
	SetShader(ShaderPath + L"Blur.hlsl");
}

NormalBlur::~NormalBlur()
{
	SAFE_DELETE(buffer);
}

void NormalBlur::Update()
{
	//TextureRect::Update();
	D3DXMATRIX velocity;
	//D3DXMatrixTranslation(&velocity, transform->velocity.x, transform->velocity.y, transform->velocity.z);
	//D3DXMatrixTranslation(&T, transform->position.x, transform->position.y, transform->position.z);
	D3DXMatrixTranslation(&T, WinMaxWidth/2, WinMaxHeight/2, 0);
	
	D3DXMatrixScaling(&S,WinMaxWidth, WinMaxHeight,1);
	//D3DXMatrixScaling(&S,transform->size.x, transform->size.y,transform->size.z);
	D3DXMatrixRotationZ(&R, (float)D3DXToRadian(transform->rotation));
	world = S * R *  T;
	world = velocity * Time::Delta() * world;

	wb->SetWorld(world);
}

void NormalBlur::Render()
{
	buffer->SetPSBuffer(0);
	TextureRect::Render();

}
