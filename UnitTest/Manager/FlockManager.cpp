#include "stdafx.h"
#include "FlockManager.h"

void FlockManager::Update()
{
	for (auto flock : flockMap)
	{
		flock.second->Update();
	}
}

void FlockManager::PushFlock(string key, FlockAI::FlockAgent * agent)
{
	auto result = flockMap.find(key);
	assert(result != flockMap.end());
	result->second->PushAgent(agent);
}

FlockAI::Flock * FlockManager::GetFlock(string key) 
{
	auto result = flockMap.find(key);
	if (result == flockMap.end())
	{
		FlockAI::Flock * flock = new FlockAI::Flock();
		flockMap.insert(make_pair(key, flock));
		return flock;
	}
	else
		return result->second;
}

FlockManager::FlockManager()
{
	//flock = new FlockAI::Flock();

}

FlockManager::~FlockManager()
{
	for (auto flock : flockMap)
	{
		flock.second->ClearAgents();
		SAFE_DELETE(flock.second);
	}
	flockMap.clear();
}
