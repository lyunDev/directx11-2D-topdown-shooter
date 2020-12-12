#include "stdafx.h"
#include "FlockAgent.h"
#include "Game/Transform.h"
#include "Game/GameObject.h"
#include "Flock.h"
#include <math.h>
#include <DirectXMath.h>
#include <random>

FlockAI::FlockAgent::FlockAgent(ActorInfo actorInfo, Vector3 position, Vector3 size, Flock * flock)
	: Actor(actorInfo, position, size,0,false)
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/¬³ricket.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetObjectLayer(ObjectLayer::ENEMY);
	SetRenderLayer(RenderLayer::ENEMY);
	agentFlock = flock;
}


void FlockAI::FlockAgent::Move(Vector3 velocity)
{
	if (currentVelocity != Values::ZeroVec3)
	{
		D3DXVec3Lerp(&currentVelocity, &currentVelocity, &velocity, 0.5f);
	}
	else
	{
		currentVelocity = velocity;
	}
	float angle = DxMath::GetAngle(Values::UpVec, currentVelocity);


	D3DXVec3Lerp(&transform->position, &transform->position, &(transform->position + currentVelocity), Time::Delta());

	if (std::abs(angle - transform->rotation) > FLT_EPSILON)
	{

		transform->rotation = DxMath::LerpDegrees(transform->rotation, angle, 10 * Time::Delta());

	}
	transform->position.z = 0;
	
}
