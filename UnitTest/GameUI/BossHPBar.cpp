#include "stdafx.h"
#include "BossHPBar.h"
#include "UI/Pannel.h"
#include "UI/ProgressBar.h"
#include "ShaderBuffers/UIElementBuffer.h"
BossHPBar::BossHPBar()
	: Pannel(Vector3(WinMaxWidth / 2, WinMaxHeight - 30, 0), Vector3(WinMaxWidth / 2, 50, 1),false)
{

	Texture2D * tex = new Texture2D(TexturePath + L"UI/EmptyBar.png");
	SetSRV(tex->GetSRV());

	Pannel * pannel2 = new Pannel(TexturePath + L"UI/BlueBar.png", Vector3(WinMaxWidth / 2, WinMaxHeight - 30, 0), Vector3(WinMaxWidth / 2, 50, 1), false);
	pannel2-> GetUIElementBuffer()->SetProcessAmount(0.5f);
}

BossHPBar::~BossHPBar()
{
}

void BossHPBar::OnUpdate()
{
}
