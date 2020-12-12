#include "stdafx.h"
#include "CohesionBehaviour.h"
#include "Game/Transform.h"
#include "FlockAgent.h"
#include "Flock.h"
Vector3 FlockAI::CohesionBehaviour::CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock)
{
	// if no neighbors, return no adjustment
	if (context.size() == 0)
		return Values::ZeroVec3;

	// add all points together and average.
	Vector3 cohesionMove = Values::ZeroVec3;
	for (auto item : context)
	{
		/*if (DxMath::GetDist(item->position, agent->transform->position) <= flock->cohesionDisance)
			continue;*/
		cohesionMove += item->position;
	}
	cohesionMove /= context.size();

	// create offset from agent position
	cohesionMove -= agent->transform->position;
	/*if (DxMath::Length(cohesionMove) <= flock->avoidDistance + 5)
		return Values::ZeroVec3;*/
	D3DXVec3Lerp(&cohesionMove, &agent->transform->GetLocalUpDirection(), &cohesionMove, 0.5f);
	return cohesionMove;
}
