#pragma once
#include "Game/GameObject.h"
#include "Game/Transform.h"


struct ActorInfo
{
	float maxHp;
	float currentHp;
	float moveSpeed;
	bool isDie;
	ActorInfo() = default;
	ActorInfo(float maxHp, float moveSpeed)
	{
		this->maxHp = maxHp;
		this->currentHp = maxHp;
		this->moveSpeed = moveSpeed;
		isDie = false;
	}

	void Hit(float damage)
	{
		if (isDie) return;
		if (currentHp - damage <= 0)
		{
			currentHp = 0;
			isDie = true;
		}
		else
		{
			currentHp -= damage;
		}
	}
};

class Actor :public GameObject
{
public :
	Actor(ActorInfo actorInfo, Vector3 position, Vector3 size, float rotation, bool hasAnimation);

	virtual void OnRespawn(Vector3 respawnPos, float respawnRot) 
	{
		actorInfo.currentHp = actorInfo.maxHp;
		actorInfo.isDie = false;
		transform->position = respawnPos;
		transform->rotation = respawnRot;
	};
	virtual void OnRelease() {};
	virtual void Hit(float damage) {};

	float GetMoveSpeed()
	{
		return actorInfo.moveSpeed;
	}
	ActorInfo GetActorInfo()
	{
		return actorInfo;
	}
	ActorInfo * GetActorInfoPtr()
	{
		return &actorInfo;
	}
protected :

	ActorInfo actorInfo;
};