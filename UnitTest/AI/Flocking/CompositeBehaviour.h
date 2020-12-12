#pragma once

#include "IFlockBehaviour.h"
#include "AlignmentBehaviour.h"
#include "CohesionBehaviour.h"
#include "StayInRadiusBehaviour.h"
#include "SteeredCohesionBehaviour.h"
#include "AvoidanceBehaviour.h"
#include "CohereToCenterBehaviour.h"
#include "RandomMovementBehaviour.h"
namespace FlockAI
{
	class CompositeBehaviour : public IFlockBehaviour
	{
	public :


		// IFlockBehaviour을(를) 통해 상속됨
		virtual Vector3 CalculateMove(FlockAgent * agent, vector<Transform*> context, Flock * flock) override;

	private :
		vector<IFlockBehaviour *> behaviours
		{
			new CohesionBehaviour(),
			new AlignmentBehaviour(),
			new AvoidanceBehaviour(),
			new StayInRadiusBehaviour(),
			new RandomMovementBehaviour(),
		};
		vector<float> weights
		{
			0.2f,
			0.3f,
			0.3f,
			0.03f,
			0.03f,
		};
	};
}