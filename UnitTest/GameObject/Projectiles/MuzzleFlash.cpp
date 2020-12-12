#include "stdafx.h"
#include "MuzzleFlash.h"
#include "ShaderBuffers/AlphaBuffer.h"
#include "Game/Transform.h"
#include "Game/GameObjectManager.h"
MuzzleFlash::MuzzleFlash(Vector3 size)
	: GameObject(Vector3(0, 0, 0), size, 0, false)
{
	SetActive(false);
	SetObjectLayer(ObjectLayer::EFFECT);
	SetRenderLayer(RenderLayer::PROJECTILE);
}

void MuzzleFlash::OnUpdate()
{
	if (GetAlphaBuffer()->GetAlpha() > 0 && GetActive() == true)
		GetAlphaBuffer()->DecreaseAlpha(7 * Time::Delta());
	else if (GetAlphaBuffer()->GetAlpha() <= 0)
		SetActive(false);
}

void MuzzleFlash::OnDisable()
{
}

void MuzzleFlash::Flash(Transform * fireTr)
{

	transform->position = fireTr->position;
	transform->rotation = fireTr->rotation;
	GetAlphaBuffer()->SetAlpha(1);
	SetActive(true);
	GeometryUpdate();
}

