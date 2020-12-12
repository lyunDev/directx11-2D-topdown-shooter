#include "stdafx.h"
#include "Actor.h"

Actor::Actor(ActorInfo actorInfo, Vector3 position, Vector3 size, float rotation, bool hasAnimation)
	: GameObject(position, size, rotation, hasAnimation)
{
	this->actorInfo = actorInfo;
	SetRigidbody(true);
}
