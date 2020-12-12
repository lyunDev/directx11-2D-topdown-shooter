#pragma once
#include "Game/GameObject.h"
#include "GameObject/Actor.h"
class Transofrm;
namespace FlockAI
{
	class Flock;
	class FlockAgent : public Actor
	{
	public :
		FlockAgent(ActorInfo actorInfo,  Vector3 position, Vector3 size, Flock * flock);

		void Move(Vector3 velocity);

	private:
		Flock * agentFlock;
	public :
		Vector3 currentVelocity = Values::ZeroVec3;
		Vector3 randomDir = Values::ZeroVec3;
		float currentRandomDelay = 0;
	};
}