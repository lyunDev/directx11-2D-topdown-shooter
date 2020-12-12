#include "stdafx.h"
#include "SteeredCohesionBehaviour.h"
#include "Game/Transform.h"
#include "FlockAgent.h"
#include "Flock.h"
Vector3 FlockAI::SteeredCohesionBehaviour::CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock)
{
	// if no neighbors, return no adjustment
	if (context.size() == 0)
		return Values::ZeroVec3;

	float nCohesion = 0;
	// add all points together and average.
	Vector3 cohesionMove = Values::ZeroVec3;
	for (auto item : context)
	{
		/*if (DxMath::GetDist(item->position, agent->transform->position) > flock->cohesionDisance)
		{*/
		if (DxMath::GetDist(item->position, agent->transform->position) > flock->avoidDistance)
		{
			nCohesion++;
			cohesionMove += item->position;
		}
		//}
	}
	if (nCohesion > 0)
		cohesionMove /= nCohesion;
	else
		return Values::ZeroVec3;
	// create offset from agent position
	cohesionMove -= agent->transform->position;

	cout << "x : " << cohesionMove.x << ", y : " << cohesionMove.y << endl;
	
	float a = DxMath::Length(cohesionMove);
	cout << "length : " << a << endl; 
	if (DxMath::Length(cohesionMove) <= 30)
		return Values::ZeroVec3;
	//D3DXVec3Lerp(&cohesionMove, &agent->transform->GetLocalUpDirection(), &cohesionMove, agentSmoothTime);
	/*float angle = DxMath::GetAngle(Values::UpVec, cohesionMove);
	agent->transform->rotation = DxMath::Lerp(agent->transform->rotation, angle, 2 * Time::Delta());*/
	return cohesionMove;
}
