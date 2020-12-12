#include "stdafx.h"
#include "BossCautionPannel.h"
#include "ShaderBuffers/AlphaBuffer.h"

BossCautionPannel::BossCautionPannel()
	: Pannel(Vector3(WinMaxWidth * 0.5f,WinMaxHeight * 0.5f, 0), Vector3(700, 300, 1),false )
{
	Texture2D * tex = new Texture2D(TexturePath + L"UI/Warning.png");
	SetSRV(tex->GetSRV());

	SetActive(false);
}


void BossCautionPannel::OnUpdate()
{
	if (isStart == true && loopingCount < maxLoopingCount)
	{
		if (isDecreaseAlpha)
		{
			if (GetAlphaBuffer()->GetAlpha() <= 0)
			{
				isDecreaseAlpha = false;
				loopingCount++;
			}
			else
				GetAlphaBuffer()->DecreaseAlpha(Time::Delta());
		}
		else
		{
			if (GetAlphaBuffer()->GetAlpha() >= 1)
				isDecreaseAlpha = true;
			else
				GetAlphaBuffer()->IncreaseAlpha(Time::Delta());
		}
	}
	if (loopingCount >= maxLoopingCount)
		SetActive(false);
}

void BossCautionPannel::Caution()
{
	isStart = true;
	isDecreaseAlpha = false;
	loopingCount = 0;
	GetAlphaBuffer()->SetAlpha(0);
	SetActive(true);
	GeometryUpdate();
}
