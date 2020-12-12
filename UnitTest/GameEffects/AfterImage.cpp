#include "stdafx.h"
#include "AfterImage.h"
#include "Game/Transform.h"
#include "ShaderBuffers/AlphaBuffer.h"

AfterImage::AfterImage(const Transform * transform)
	: GameObject(transform->position, transform->size, transform->rotation, false)
{
	//SetShader(ShaderPath + L"AlphaTexture.hlsl");

	SetActive(true);
	

	SetRenderLayer(RenderLayer::PROJECTILE);
	SetObjectLayer(ObjectLayer::EFFECT);
}


void AfterImage::OnUpdate()
{
	if (GetAlphaBuffer()->GetAlpha() > 0 && GetActive() == true)
	{
		GetAlphaBuffer()->DecreaseAlpha(0.7f * Time::Delta());
	}
}

void AfterImage::OnPostUpdate()
{
	if (GetAlphaBuffer()->GetAlpha() == 0)
	{
		delete this;
	}
}

void AfterImage::OnRender()
{
	//alphaBuffer->SetPSBuffer(2);
}
