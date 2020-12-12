#pragma once
#include "AI/Flocking/FlockAgent.h"
#include "AI/Flocking/Flock.h"

class FlockManager : public SingletonBase<FlockManager>
{
	friend class SingletonBase<FlockManager>;

public :

	void Update();

	void PushFlock(string key, FlockAI::FlockAgent * agent);
	FlockAI::Flock * GetFlock(string key);
private :
	unordered_map<string, FlockAI::Flock * > flockMap;
private :
	FlockManager();
	~FlockManager();

};