#include "stdafx.h"
#include "Shield.h"
#include "ShaderBuffers/AlphaBuffer.h"
#include "Game/Transform.h"
Shield::Shield(GameObject * owner, Vector3 size, float energyMax)
	:GameObject(Vector3(0, 0, 0), size, 0, false)
	, owner(owner)
	, energyMax(energyMax)
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Effect/shield_Edit.png");
	SetSRV(tex->GetSRV());

	SetActive(false);
}

void Shield::OnUpdate()
{
	if (currentEnergy <= 0)
		SetActive(false);
	float healFactor = healingEnergy * Time::Delta();
	if ((currentEnergy + healFactor) >= energyMax)
		currentEnergy = energyMax;
	else
		currentEnergy += healFactor;

	float alphaDest = currentEnergy / energyMax;
	currentAlpha = DxMath::Lerp(alphaDest, currentAlpha, Time::Delta());
	GetAlphaBuffer()->SetAlpha(currentAlpha);

	transform->position = owner->transform->position;
}

void Shield::ActiveShield()
{
	currentEnergy = energyMax;
	GetAlphaBuffer()->SetAlpha(1);
	transform->position = owner->transform->position;
	SetActive(true);
	GeometryUpdate();
}

void Shield::HitShield(float damage)
{
	if (currentEnergy - damage <= 0)
		currentEnergy = 0;
	else
		currentEnergy -= damage;
}
