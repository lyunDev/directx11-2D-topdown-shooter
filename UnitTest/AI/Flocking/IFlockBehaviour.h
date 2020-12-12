#pragma once
#include "stdafx.h"


class Transform;
namespace FlockAI
{

	class FlockAgent;
	
	class Flock;
	class IFlockBehaviour
	{
	public :
		virtual Vector3 CalculateMove(FlockAgent* agent, vector<Transform*> context, Flock* flock) { return Values::ZeroVec3; }
	};
}