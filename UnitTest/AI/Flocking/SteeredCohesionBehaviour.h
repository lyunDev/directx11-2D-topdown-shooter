#pragma once
#include "IFlockBehaviour.h"

namespace FlockAI
{
	class SteeredCohesionBehaviour : public IFlockBehaviour
	{
	public :


		// IFlockBehaviour을(를) 통해 상속됨
		virtual Vector3 CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock) override;

	private :
		Vector3 currentVelocity; 
		float agentSmoothTime = 0.5f;
	};
}