#include "stdafx.h"
#include "PlayerHPBar.h"
#include "GameObject/Actor.h"
#include "ShaderBuffers/ProgressBuffer.h"
#include "Game/Transform.h"

PlayerHPBar::PlayerHPBar(Vector3 position, Vector3 size)
	: Pannel(position, size, false)
{
	SetShader(ShaderPath + L"ProgressBarOnUI.hlsl");
	
	progressBuffer = new ProgressBuffer();
	Texture2D *	progressTex = new Texture2D(TexturePath + L"UI/HealthBarFill.png");
	SetSRV(progressTex->GetSRV());
	Texture2D * backgroundTex = new Texture2D(TexturePath + L"UI/HealthBar.png");
	backgroundSRV = backgroundTex->GetSRV();

	SetObjectLayer(ObjectLayer::UI);
	SetRenderLayer(RenderLayer::UI);
	SetActive(true);
}

PlayerHPBar::~PlayerHPBar()
{
	SAFE_DELETE(progressBuffer);
}

void PlayerHPBar::SetPlayer(GameObject * player)
{
	this->owner = player;
	Actor* actor = static_cast<Actor*>(player);
	this->actorInfo = actor->GetActorInfoPtr();
}

void PlayerHPBar::OnUpdate()
{
	UIElement::OnUpdate();
	if (owner == nullptr)
		return;
	if (actorInfo == nullptr)
		return;
	
	if (progressBuffer->GetProcessAmount() <= 0 || actorInfo->currentHp <= 0)
	{
		progressBuffer->SetProcessAmount(0);
		return;
	}
	else
	{
		progressBuffer->SetProcessAmount((float)actorInfo->currentHp / actorInfo->maxHp);
	}
}

void PlayerHPBar::OnRender()
{
	UIElement::OnRender();
	DC->PSSetShaderResources(3, 1, &backgroundSRV);
	progressBuffer->SetPSBuffer(6);
}
