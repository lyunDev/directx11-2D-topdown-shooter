#include "stdafx.h"
#include "AlignmentBehaviour.h"
#include "Game/Transform.h"
#include "FlockAgent.h"
#include "Game/GameObjectManager.h"

Vector3 FlockAI::AlignmentBehaviour::CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock)
{
	/*Vector3 dir = GameObjectManager::Get()->GetPlayer()->transform->position - agent->transform->position;
	dir = DxMath::Normalize(dir);
	return dir * 100;*/
	// if no neighbors, maintain current alignment.
	if (context.size() == 0)
		return agent->transform->GetLocalUpDirection() * 100;
	Vector3 alignmentMove = Values::ZeroVec3;

	for (auto item : context)
	{
		alignmentMove += item->GetLocalUpDirection();
		//alignmentMove += Values::UpVec;
	}
	alignmentMove /= context.size();
	//return Values::UpVec;
	//alignmentMove = Values::UpVec;
	alignmentMove = DxMath::Normalize(alignmentMove);

	return alignmentMove * 100;
}