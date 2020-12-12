#include "stdafx.h"
#include "FadeInOut.h"

#include "ShaderBuffers/AlphaBuffer.h"
FadeInOut::FadeInOut()
	: Pannel(Vector3(WinMaxWidth * 0.5f ,WinMaxHeight * 0.5f, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), false)
{
	Texture2D * tex = new Texture2D(TexturePath + L"fade.png");
	SetSRV(tex->GetSRV());

	SetActive(false);
	SetRenderLayer(RenderLayer::UI2);
}

void FadeInOut::OnUpdate()
{
	if (isFadeIn)
	{
		if (GetAlphaBuffer()->GetAlpha() <= 0)
		{
			fadeInCompleted();
			SetActive(false);
		}
		GetAlphaBuffer()->DecreaseAlpha(Time::Delta());
	}
	else
	{
		if (GetAlphaBuffer()->GetAlpha() >= 1)
		{
			fadeOutCompleted();
			SetActive(false);
		}
		GetAlphaBuffer()->IncreaseAlpha(Time::Delta());
	}
}

void FadeInOut::FadeIn(function<void(void)> fadeInCompleted)
{
	this->fadeInCompleted = fadeInCompleted;
	GetAlphaBuffer()->SetAlpha(1);
	SetActive(true);
	GeometryUpdate();
	isFadeIn = true;
}

void FadeInOut::FadeOut(function<void(void)> fadeOutCompleted)
{
	this->fadeOutCompleted = fadeOutCompleted;
	GetAlphaBuffer()->SetAlpha(0);
	SetActive(true);
	GeometryUpdate();
	isFadeIn = false;
}
