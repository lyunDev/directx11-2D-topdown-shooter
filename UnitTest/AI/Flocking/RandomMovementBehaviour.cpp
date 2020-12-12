#include "stdafx.h"
#include "RandomMovementBehaviour.h"
#include "Game/Transform.h"
#include "Game/GameObjectManager.h"
#include "GameObject/Player.h"
#include "FlockAgent.h"
#include <random>
Vector3 FlockAI::RandomMovementBehaviour::CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock)
{

	agent->currentRandomDelay += Time::Delta();
	if (agent->currentRandomDelay > randomResetDelay)
	{
		agent->currentRandomDelay = 0;
		Transform tr;
		tr.position = agent->transform->GetLocalUpDirection();
		tr.Rotate(DxMath::ReliableRandom(minRotate, maxRotate));
		agent->randomDir = tr.position;
	}
	return agent->randomDir * weightFactor;
} 
