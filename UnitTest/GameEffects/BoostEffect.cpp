#include "stdafx.h"
#include "BoostEffect.h"
#include "Game/Transform.h"
#include "ShaderBuffers/AlphaBuffer.h"

BoostEffect::BoostEffect()
	: GameObject(Vector3(0, 0, 0), Vector3(100, 100, 1), 0, false)
{

	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Boost.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetShader(ShaderPath + L"AlphaTexture.hlsl");

	SetActive(false);
	alphaBuffer = new AlphaBuffer();
}

BoostEffect::~BoostEffect()
{
	SAFE_DELETE(alphaBuffer);
}

void BoostEffect::OnUpdate()
{
	if (alphaBuffer->GetAlpha() > 0 && GetActive() == true)
	{
		alphaBuffer->DecreaseAlpha(0.2f * Time::Delta());
	}
	else if (alphaBuffer->GetAlpha() == 0)
	{
		SetActive(false);
	}
}

void BoostEffect::OnRender()
{
	alphaBuffer->SetPSBuffer(2);
}

void BoostEffect::SetTr(Transform * tr)
{
	SetActive(true);
	alphaBuffer->SetAlpha(1);
	//transform = fireTr;
	transform = tr;
	/*transform->position = tr.position;
	transform->size = tr.size;
	transform->rotation = tr.rotation;*/
}

