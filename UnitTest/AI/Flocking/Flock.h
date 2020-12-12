#pragma once
class Transform;

namespace FlockAI
{
	class FlockAgent;
	class IFlockBehaviour;
	class Flock
	{

	public:
		Flock();
		void Update();
		void PushAgent(FlockAgent * flockAgent);
		void ClearAgents();
		vector<Transform *> GetNearbyObjects(FlockAgent * agent);
	private:
		vector<FlockAgent*> agents;
		IFlockBehaviour * behaviour;
	public :
	private:
		
		/*float startingCount = 4;
		float agentDensity = 0.08f;*/
		// 1 ~ 100
		float driveFactor = 4;
		// 1 ~ 100
		float maxSpeed = 100;
	public :
	
		float avoidDistance = 25;
		//float cohesionDisance = 90;
		float neighborDistance = 50;

		float flockDelay = 0.5f;
		float currentFlockDelay = 0;
	};
}