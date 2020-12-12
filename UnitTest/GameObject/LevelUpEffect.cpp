#include "stdafx.h"
#include "LevelUpEffect.h"
#include "ShaderBuffers/AlphaBuffer.h"
#include "Game/Transform.h"
#include "Game/GameObjectManager.h"

LevelUpEffect::LevelUpEffect()
	: GameObject(Vector3(0, 0, 0), Vector3(100, 80, 1), 0, false)
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Effect/levelUp.png");
	SetSRV(tex->GetSRV());

	SetActive(false);
	SetObjectLayer(ObjectLayer::UI);
	SetRenderLayer(RenderLayer::UI);
}



void LevelUpEffect::OnUpdate()
{
	if (GetAlphaBuffer()->GetAlpha() > 0 && GetActive() == true)
		GetAlphaBuffer()->DecreaseAlpha(Time::Delta());
	else if (GetAlphaBuffer()->GetAlpha() <= 0)
		SetActive(false);
}

void LevelUpEffect::LevelUp(Transform * ownerTr)
{
	Vector3 offset =Vector3(0, 80, 0);
	transform->position = ownerTr->position + offset;
	GetAlphaBuffer()->SetAlpha(1);
	SetActive(true);
	GeometryUpdate();
}
