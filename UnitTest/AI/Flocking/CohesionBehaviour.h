#pragma once
#include "IFlockBehaviour.h"

namespace FlockAI
{
	class CohesionBehaviour : public IFlockBehaviour
	{
		// IFlockBehaviour을(를) 통해 상속됨
		virtual Vector3 CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock) override;
	};
}