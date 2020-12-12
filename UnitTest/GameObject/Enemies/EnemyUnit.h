#pragma once
#include "GameObject/Actor.h"
#include "Game/GameObject.h"
#include "Utilities/ObjectPool.h"
#include "GameObject/Projectiles/Bullet.h"
#include "ShaderBuffers/ColorBuffer.h"
#include "AI/FSM/FSMState.h"
#include "Effects/Dissolve.h"
#include "Game/Transform.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"
#include "Game/GameObjectManager.h"


// 외부에서 enemy의 공통 상위 클래스에 접근하기 위한 클래스
class EnemyUnitAbstract : public Actor
{
public :
	EnemyUnitAbstract(ActorInfo info, Vector3 size) 
		: Actor(info, Vector3(0, 0, 0), size, 0, false)
	{
	}
	virtual float GetEnoughCloseDist() { return 0; }
	virtual float GetChaseDist() { return 0; }
	virtual float GetMoveSpeed() { return 0; }
	virtual Vector3 GetFirePosOffset() { return Vector3(); };
};

template <typename TBulletType, typename TMuzzleType>
class EnemyUnit : public EnemyUnitAbstract
{
public :
	EnemyUnit(ActorInfo actorInfo, Vector3 size)
		: EnemyUnitAbstract(actorInfo, size)
	{
		SetTag("EnemyUnit");
		SetActive(false);
		bulletPool = new ObjectPool<TBulletType>();
		muzzleFlash = new TMuzzleType;
		firePos = new Transform();
		muzzlePos = new Transform();
		SetObjectLayer(ObjectLayer::ENEMY);
		SetRenderLayer(RenderLayer::ENEMY);
	}
	virtual ~EnemyUnit()
	{
	}

	virtual void OnCollisionEnter(GameObject* other) override
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
		if (bShootable)
		{
			FirePosUpdate();
			Fire();
			BulletUpdate();
		}
		if (enemyState)
		{
			FSMState * state = enemyState->Update(this);
			if (state != nullptr)
			{
				enemyState->Exit(this);
				SAFE_DELETE(enemyState);
				enemyState = state;
				enemyState->Enter(this);
			}
		}

		// 일정거리 이상 떨어지면 false
		auto playerPos = GameObjectManager::Get()->GetPlayer()->transform->position;
		if (DxMath::GetDist(playerPos, transform->position) >= (WinMaxWidth / 2) + 500
			 && GetTag() != "Boss")
			SetActive(false);

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

	virtual void OnRespawn(Vector3 reapawnPos, float respawnRot) override
	{
		Actor::OnRespawn(reapawnPos, respawnRot);
		GetDissolveBuffer()->SetDissolveAmount(0);
		SetActive(true);
	}

	virtual float GetEnoughCloseDist() override
	{
		return enoughCloseDist;
	}
	virtual float GetChaseDist() override
	{
		return chaseDist;
	}
	virtual float GetMoveSpeed() override
	{
		return actorInfo.moveSpeed;
	}

protected :

	void SetBulletPoolMaximum(uint maximum)
	{
		bulletMaximum = maximum;
	}
	void SetBulletRange(uint range)
	{
		bulletRange = range;
	}
	void SetShootDelay(float delay)
	{
		shootDelay = delay;
	}
	virtual Vector3 GetFirePosOffset() override { return Vector3(); };
private : // about bullet
	void FirePosUpdate()
	{
		firePos->position = GetFirePosOffset();
		firePos->size = transform->size;
		firePos->Rotate((float)D3DXToRadian(transform->rotation));
		firePos->position += transform->position;
		firePos->rotation = transform->rotation;

		muzzlePos->position = GetFirePosOffset();
		muzzlePos->size = transform->size;
		muzzlePos->Rotate((float)D3DXToRadian(transform->rotation));
		muzzlePos->position += transform->position;
		muzzlePos->rotation = transform->rotation;
	}
	void Fire()
	{
		currentShootDelay += Time::Delta();
		if (currentShootDelay >= shootDelay)
		{
			currentShootDelay = 0;
			if (activeBullets.size() >= bulletMaximum)
				return;
			auto bullet = bulletPool->AccquireObject();
			activeBullets.push_back(bullet);
			bullet->Fire(firePos);
			bullet->SetActive(true);

			muzzleFlash->Flash(muzzlePos);
			muzzleFlash->SetActive(true);
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
		// 임시 변수
		bool bShootable = true;
private :

	float chaseDist = 600;
	float enoughCloseDist = 300;

	
	protected :
	class FSMState * enemyState = nullptr;


private : // about bullet
	ObjectPool<TBulletType> * bulletPool = nullptr;
	vector<shared_ptr<TBulletType>> activeBullets;
	uint bulletMaximum = 10;
	uint bulletRange = 1000;

	TMuzzleType * muzzleFlash = nullptr;
	float shootDelay = 1.3f;
	float currentShootDelay = 0;

	Transform * firePos = nullptr;
	Transform * muzzlePos = nullptr;
};