#pragma once

#include "IFlockBehaviour.h"

namespace FlockAI
{
	class RandomMovementBehaviour : public IFlockBehaviour
	{
	public:
		// IFlockBehaviour을(를) 통해 상속됨
		virtual Vector3 CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock) override;

	private:
		Vector3 randomDir = Values::ZeroVec3;
		float randomResetDelay = 10;
		float currentDelay = 0;
		float minRotate = -20;
		float maxRotate = 20;
		float weightFactor = 100;
	};
}