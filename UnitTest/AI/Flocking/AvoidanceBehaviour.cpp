#include "stdafx.h"
#include "AvoidanceBehaviour.h"
#include "Game/Transform.h"
#include "FlockAgent.h"
#include "Flock.h"
Vector3 FlockAI::AvoidanceBehaviour::CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock)
{
	// if no neighbors , return no adjustment
	if (context.size() == 0)
		return Values::ZeroVec3;

	Vector3 avoidanceMove = Values::ZeroVec3;
	int nAvoid = 0;
	for (auto item : context)
	{
		/*if (DxMath::SqrMagnitude(item->position - agent->transform->position) < flock->squareAvoidanceRadius)
		{
			nAvoid++;
			avoidanceMove += agent->transform->position - item->position;
		}*/
		float a = std::abs(DxMath::Length(item->position - agent->transform->position));
		if (std::abs(DxMath::Length(item->position - agent->transform->position)) < flock->avoidDistance)
		{
			nAvoid++;
			avoidanceMove += agent->transform->position - item->position;
		}
	}
	if (nAvoid > 0)
		avoidanceMove /= nAvoid;
	return avoidanceMove;
}
