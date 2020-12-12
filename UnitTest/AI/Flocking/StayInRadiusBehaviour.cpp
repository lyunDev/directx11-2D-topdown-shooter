#include "stdafx.h"
#include "StayInRadiusBehaviour.h"
#include "Game/Transform.h"
#include "Game/GameObjectManager.h"
#include "GameObject/Player.h"
#include "FlockAgent.h"
Vector3 FlockAI::StayInRadiusBehaviour::CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock)
{
	center = GameObjectManager::Get()->GetPlayer()->transform->position;
	Vector3 centerOffset = center - agent->transform->position;
	float t = DxMath::Length(centerOffset) / WinMaxHeight;
	if (t < 0.9f)
	{
		return Values::ZeroVec3;
	}
	return centerOffset * t * t;
}
