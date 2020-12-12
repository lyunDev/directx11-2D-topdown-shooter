#include "stdafx.h"
#include "GameClearPannel.h"
#include "ShaderBuffers/AlphaBuffer.h"

GameClearPannel::GameClearPannel()
	: Pannel(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0), Vector3(700, 700, 1), false)
{
	Texture2D * tex = new Texture2D(TexturePath + L"UI/completed.png");
	SetSRV(tex->GetSRV());

	SetActive(false);
}

void GameClearPannel::OnUpdate()
{

	if (GetAlphaBuffer()->GetAlpha() >= 1)
	{
		currentDelay += Time::Delta();
		if (currentDelay > sceneTransitionDelay)
		{
			onCompleted();
			SetActive(false);
		}
	}
	else
	{
		GetAlphaBuffer()->IncreaseAlpha(0.4f * Time::Delta());
	}
}

void GameClearPannel::Clear(function<void(void)> onCompleted)
{
	this->onCompleted = onCompleted;
	GetAlphaBuffer()->SetAlpha(0);
	SetActive(true);
}
