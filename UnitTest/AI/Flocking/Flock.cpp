#include "stdafx.h"
#include "Flock.h"
#include "FlockAgent.h"
#include "CompositeBehaviour.h"
#include "Game/GameObjectManager.h"
#include "Game/Transform.h"
//void Flock::Flock::Init()
//{
//	behaviour = new CompositeBehaviour();
//
//	/*for (int i = 0; i < startingCount; i++)
//	{
//		FlockAgent * newAgent = new FlockAgent(Vector3(WinMaxWidth / 2 - i * 105, WinMaxHeight / 2, 0), Vector3(100, 100, 1));
//		newAgent->Initialize(this);
//		agents.push_back(newAgent);
//	}*/
//	/*FlockAgent * newAgent2 = new FlockAgent(Vector3(WinMaxWidth / 2 - 500, WinMaxHeight / 2, 0), Vector3(100, 100, 1));
//	newAgent2->Initialize(this);
//	agents.push_back(newAgent2);*/
//}
FlockAI::Flock::Flock()
{
	behaviour = new CompositeBehaviour();
}
void FlockAI::Flock::Update()
{
	for (auto agent : agents)
	{
		vector<Transform*> context = GetNearbyObjects(agent);

		Vector3 move = behaviour->CalculateMove(agent, context, this);
		move *= driveFactor;

		agent->Move(move);
	}
}

void FlockAI::Flock::PushAgent(FlockAgent * flockAgent)
{
	agents.push_back(flockAgent);
}

void FlockAI::Flock::ClearAgents()
{
	agents.clear();
}


vector<Transform*> FlockAI::Flock::GetNearbyObjects(FlockAgent * agent)
{
	vector<Transform * > context;
	
	// TODO : 일정 거리 안에 있는 agent들만 푸시
	/*for (auto item : agents)
	{
		if (agent == item) continue;
		if(DxMath::GetDist(agent->transform->position, item->transform->position) < neighborDistance)
			context.push_back(item->transform);
	}*/

	// 시야각으로 판별
	float radiusFactor = 30;
	// 1 = 45도 늘어날수록 점점 각도가 커짐
	float _FRONT_VIEW_ANGLE_FACTOR = 1.f;
	float _BACK_VIEW_ANGLE_FACTOR = 1;
	for (auto unit : agents)
	{
		if (unit == agent) continue;
		Vector3 dir = unit->transform->position - agent->transform->position;
		Transform tr;
		tr.position = dir;
		tr.Rotate(D3DXToRadian(agent->transform->rotation));
		Vector3 rotatedDir = tr.position;
		bool wideView = true;
		bool limitedView = false;
		bool narrowView = false;
		bool inView = false;
		if (wideView)
		{
			inView = ((rotatedDir.y > 0) || ((rotatedDir.y < 0) &&
				fabs(rotatedDir.x) > fabs(rotatedDir.y) * _BACK_VIEW_ANGLE_FACTOR));
		}
		if (limitedView)
		{
			inView = (rotatedDir.y > 0);
		}
		if (narrowView)
		{
			// narrow view
			inView = (((rotatedDir.y > 0) && (fabs(rotatedDir.x) < fabs(rotatedDir.y) *
				_FRONT_VIEW_ANGLE_FACTOR)));
		}
		if (inView)
		{
			if (DxMath::Length(dir) <= neighborDistance)
			{
				context.push_back(unit->transform);
			}
		}
	}
	return context;
}
