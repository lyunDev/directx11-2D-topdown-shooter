#pragma once
#include "AI/Flocking/FlockAgent.h"
#include "AI/Flocking/Flock.h"
#include "GameObject/Actor.h"
#include "Utilities/ObjectPool.h"
#include "Utilities/Layers.h"
#include "Game/RenderManager.h"
#include "Game/GameObjectManager.h"
#include "GameObject/Projectiles/Bullet.h"
#include "ShaderBuffers/ColorBuffer.h"
#include "Effects/Dissolve.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"

using namespace FlockAI;

class EnemyFlockAbstract : public FlockAgent
{
public :
	EnemyFlockAbstract(ActorInfo info, Vector3 size, Flock* flock)
		: FlockAgent(info, Vector3(0, 0, 0), size, flock)
	{

	}

};


template <typename TBulletType>
class EnemyFlock : public EnemyFlockAbstract
{
public:
	EnemyFlock(ActorInfo info, Vector3 size, Flock * flock)
		: EnemyFlockAbstract(info, size, flock)
	{
		SetTag("EnemyFlock");
		SetActive(false);
		bulletPool = new ObjectPool<TBulletType>();
		firePoses.assign(4, Transform());
		for (int i = 0; i < bulletMaximum; i++)
		{
			auto bullet = bulletPool->AccquireObject();
			activeBullets.push_back(bullet);
		}
		for (auto bullet : activeBullets)
		{
			bulletPool->ReleaseObject(bullet);
		}
		activeBullets.clear();

		SetObjectLayer(ObjectLayer::ENEMY);
		SetRenderLayer(RenderLayer::ENEMY);
	}
	virtual ~EnemyFlock()
	{
		SAFE_DELETE(bulletPool);
	}

	virtual void OnCollisionEnter(GameObject * other) override
	{
		GameObject::OnCollisionEnter(other);
		if (other->GetObjectLayer() == ObjectLayer::PLAYER_BULLET)
		{
			Bullet * bullet = static_cast<Bullet *>(other);
			if (bullet == nullptr) return;
			Hit(bullet->GetBulletInfo().damage);
		}
	}
	virtual void Hit(float damage) override
	{
		GetColorBuffer()->SetColor(Color(1, 1, 1, 0));
		actorInfo.Hit(damage);
	}
	virtual void OnUpdate() override
	{
		Fire();
		BulletUpdate();
		if (actorInfo.isDie)
		{
			GetDissolveBuffer()->IncreaseDissolveAmount(Time::Delta());
			if (GetDissolveBuffer()->GetDissolveAmount() >= 1)
			{
				SetActive(false);
				EventDispatcher::TriggerEvent(BattleEvent::KillEnemy);
			}
		}
	}
	virtual void OnPostRender() override
	{
		if (GetColorBuffer()->GetColor() == Color(1, 1, 1, 0))
			GetColorBuffer()->SetColor(Color(0, 0, 0, 0));
	}
	virtual void OnRespawn(Vector3 respawnPos, float respawnRot) override
	{
		Actor::OnRespawn(respawnPos, respawnRot);
		GetDissolveBuffer()->SetDissolveAmount(0);
		SetActive(true);
	}
	void Fire()
	{
		currentShootDelay += Time::Delta();
		if (currentShootDelay >= shootDelay)
		{
			currentShootDelay = 0;
			rotOffset = 0;
			for(int i = 0; i < 4; i++)
			{
				if (activeBullets.size() >= bulletMaximum)
					return;
				rotOffset += i * 90;
				auto bullet = bulletPool->AccquireObject();
				activeBullets.push_back(bullet);

				firePoses[i].position = Vector3(0, 5, 0);
				firePoses[i].Rotate((float)D3DXToRadian(rotOffset));
				firePoses[i].position += transform->position;
				firePoses[i].rotation = rotOffset;
				bullet->Fire(&firePoses[i]);
			}
		}
	}
	void BulletUpdate()
	{
		for (int i = 0; i < activeBullets.size(); i++)
		{
			float length = D3DXVec3Length(&(transform->position - activeBullets[i]->transform->position));
			if (length >= bulletRange || activeBullets[i]->GetActive() == false)
			{
				bulletPool->ReleaseObject(activeBullets[i]);
				activeBullets.erase(activeBullets.begin() + i);
			}
		}
	}
protected :
	float SetBulletPoolMaximum(uint maximum)
	{
		bulletMaximum = maximum;
	}
	float SetBulletRange(uint range)
	{
		bulletRange = range;
	}
	void SetShootDelay(float delay)
	{
		shootDelay = delay;
	}
private : // about bullet
	ObjectPool<TBulletType> * bulletPool = nullptr;
	vector<shared_ptr<TBulletType>> activeBullets;
	vector<Transform> firePoses;
	int rotOffset = 0;
	uint bulletMaximum = 12;
	uint bulletRange = 1000;
	float shootDelay = 5;
	float currentShootDelay = 0;
};