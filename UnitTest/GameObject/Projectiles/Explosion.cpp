#include "stdafx.h"
#include "Explosion.h"
#include "Utilities/Animator.h"
#include "Game/Transform.h"
#include "ShaderBuffers/AlphaBuffer.h"
#include "Utilities/Layers.h"
#include "Game/GameObjectManager.h"
#include "GameObject/Actor.h"

Explosion::Explosion(Vector3 size)
	: GameObject(Vector3(0, 0, 0), size, 0, true)
{
	GetAnimator()->AnimStop();

	SetActive(false);
	SetObjectLayer(ObjectLayer::EFFECT);
	SetRenderLayer(RenderLayer::GAMEOBJECT);
}


void Explosion::OnUpdate()
{
	if (GetAlphaBuffer()->GetAlpha() > 0
		&& GetActive() == true
		&& isAnimCompleted)
	{
		GetAlphaBuffer()->DecreaseAlpha(7 * Time::Delta());
	}
	else if (GetAlphaBuffer()->GetAlpha() <= 0)
		SetActive(false);
}

void Explosion::OnEnable()
{

}

void Explosion::OnDisable()
{
}

void Explosion::Explode(Transform * explodeTr)
{
	transform->position = explodeTr->position;
	transform->rotation = explodeTr->rotation;
	GetAlphaBuffer()->SetAlpha(1);
	isAnimCompleted = false;
	SetActive(true);
	GetAnimator()->AnimRestart();
	GetAnimator()->onAnimationFinished = [&]()->void 
	{
		GetAnimator()->AnimStop(); 
		isAnimCompleted = true; 
	};
	GeometryUpdate();
/*
	if (attackRange != 0 && damage != 0)
	{
		vector<GameObject*> findObjs;
		if (ownerLayer == ObjectLayer::ENEMY || ownerLayer == ObjectLayer::ENEMY_BULLET)
		{
			findObjs.push_back(GameObjectManager::Get()->GetPlayer());
		}
		else if (ownerLayer == ObjectLayer::PLAYER || ownerLayer == ObjectLayer::PLAYER_BULLET)
		{
			findObjs = GameObjectManager::Get()->FindObjectsWithDistance(this, attackRange, ObjectLayer::ENEMY);
		}
		for (auto obj : findObjs)
		{
			Actor * actor = static_cast<Actor *>(obj);
			assert(actor != nullptr);
			actor->Hit(damage);
		}
	}*/
}
