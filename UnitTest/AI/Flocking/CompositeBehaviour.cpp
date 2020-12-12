#include "stdafx.h"
#include "CompositeBehaviour.h"
#include "FlockAgent.h"

Vector3 FlockAI::CompositeBehaviour::CalculateMove(
	FlockAgent * agent, vector<Transform*> context, Flock * flock)
{
	assert(weights.size() == behaviours.size());

	Vector3 move = Values::ZeroVec3;

	for (int i= 0; i < behaviours.size(); i++)
	{
		Vector3 partialMove = behaviours[i]->CalculateMove(agent, context, flock);
		if (partialMove != Values::ZeroVec3)
		{
			move += partialMove * weights[i];
		}
	}

	return move;
}

