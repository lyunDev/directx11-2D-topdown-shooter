#pragma once
#include "Utilities/ObjectPool.h"
#include <future>
#include <mutex>
#include <thread>
struct IRespawnData
{
public :
	virtual void Update(Vector3 resapwnPos, float respawnRotation) {};
};

// only actor 
template <typename RespawnType>
class RespawnData : public IRespawnData
{
public :
	RespawnData(float respawnDelay, uint poolMaximum, float startRespawnTime, float endRespawnTime)
		: respawnDelay(respawnDelay), poolMaximum(poolMaximum), currentRespawnDelay(0),
		startRespawnTime(startRespawnTime), endRespawnTime(endRespawnTime), currentRespawnTime(0)
	{
		/*std::async(std::launch::async, [&]() 
		{*/
			//m.lock();
			auto obj = pool.AccquireObject();
			pool.ReleaseObject(obj);
			//m.unlock();
		//});
		// 미리 로드
	
	}

	virtual void Update(Vector3 respawnPos, float respawnRotation) override
	{

		for (int i = 0; i < activeObj.size(); i++)
		{
			if (activeObj[i].get()->GetActive() == false)
			{
				activeObj[i].get()->OnRelease();
				pool.ReleaseObject(activeObj[i]);
				activeObj.erase(activeObj.begin() + i);
			}
		}

		currentRespawnTime += Time::Delta();
		if (currentRespawnTime < startRespawnTime)
			return;
		if (currentRespawnTime > endRespawnTime)
			return;

		currentRespawnDelay += Time::Delta();
		if (currentRespawnDelay >= respawnDelay && activeObj.size() < poolMaximum)
		{
			currentRespawnDelay = 0;
			auto obj = pool.AccquireObject();
			activeObj.push_back(obj);
			obj.get()->OnRespawn(respawnPos, respawnRotation);
		}
	}
public :
	float currentRespawnDelay;
	float respawnDelay;

	float currentRespawnTime;
	float startRespawnTime;
	float endRespawnTime;

	uint poolMaximum;
	ObjectPool<RespawnType> pool;
	vector<shared_ptr<RespawnType>> activeObj;
};
class RespawnManager : public SingletonBase<RespawnManager>
{
	friend class SingletonBase<RespawnManager>;


public :
	void Update();
private :
	RespawnManager();
	virtual ~RespawnManager();

	
private :
	vector<IRespawnData *> respawns;
	std::future< vector<IRespawnData *>> f;
};