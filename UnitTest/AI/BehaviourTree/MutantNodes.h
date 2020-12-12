#pragma once
#include "stdafx.h"
#include "Utilities/BrainTree.h"
#include "Game/GameObjectManager.h"
#include "GameObject/Player.h"
#include "GameObject/Enemies/EnemyUnit.h"
#include "GameObject/Skills/Shield.h"
#include "GameObject/Skills/WideExplosion.h"
#include "GameEffects/AfterImage.h"
#include "Utilities/ObjectPool.h"
// юс╫ц
#include "GameObject/Projectiles/WarWeaponBullet.h"
#include "GameObject/Projectiles/WarWeaponMuzzleFlash.h"

#include "GameObject/Enemies/EnemyUnit.h"


class MovingAction : public BrainTree::UntilSuccess
{
public :
	MovingAction(GameObject * owner)
		: owner(owner)
	{
	}
	void initialize() override
	{
		auto player = GameObjectManager::Get()->GetPlayer();

		float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);

		owner->transform->rotation = rotation;
		moveRot = rotation;
	}
	Status update() override
	{
		EnemyUnitAbstract * enemy = static_cast<EnemyUnitAbstract*>(owner);
		auto player = GameObjectManager::Get()->GetPlayer();

		float speed = enemy->GetMoveSpeed() * Time::Delta();
		float dist = DxMath::GetDist(player->transform->position, owner->transform->position);

		currentAfterImageDelay += Time::Delta();
		if (currentAfterImageDelay >= afterImageDelay)
		{
			currentAfterImageDelay = 0;
			AfterImage * afterImage = new AfterImage(owner->transform);
			afterImage->SetAfterImageSRV(owner->GetSRV());
		}
		if (dist < enemy->GetChaseDist())
		{
			Transform tr;
			tr.position = Vector3(0, speed, 0);
			tr.Rotate((float)D3DXToRadian(moveRot));
			owner->transform->position += tr.position;
			float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);
			owner->transform->rotation = rotation;
		}
		else
		{
			Transform tr;
			tr.position = Vector3(0, speed, 0);
			tr.Rotate((float)D3DXToRadian(owner->transform->rotation));
			owner->transform->position += tr.position;
			float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);
			owner->transform->rotation = rotation;
			moveRot = rotation;
		}

		if (dist <= enemy->GetEnoughCloseDist())
			return Node::Status::Success;
		return Node::Status::Running;
}
private :
	GameObject * owner = nullptr;
	float moveRot = 0;
	float currentAfterImageDelay = 0;
	float afterImageDelay = 0.3f;
};

class ExplosionAction : public BrainTree::Node
{
public :
	ExplosionAction(GameObject * owner)
		: owner(owner)
	{
		wideExplosion = new WideExplosion();
	}

	Status update() override
	{
		wideExplosion->Explode(owner->transform);
		auto player = GameObjectManager::Get()->GetPlayer();
		float dist = DxMath::GetDist(player->transform->position, owner->transform->position);
		if (dist <= attackDist)
		{
			Actor * actor = static_cast<Actor*>(player);
			actor->Hit(explosionDamage);
		}
		return Node::Status::Success;
	}


private :
	GameObject * owner = nullptr;
	WideExplosion * wideExplosion = nullptr;
	float attackDist = 500;
	float explosionDamage = 50;
};

class ShieldAction : public BrainTree::Node
{
public :
	ShieldAction(GameObject * owner)
		:owner(owner)
	{
		shield = new Shield(owner, Vector3(150, 150, 1), shieldEnergy);

	}
	Status update() override
	{
		shield->ActiveShield();
		return Node::Status::Success;
	}

private :
	GameObject * owner = nullptr;
	Shield * shield = nullptr;
	float shieldEnergy = 500;
};

class NormalShootAction : public BrainTree::UntilSuccess
{
public :
	NormalShootAction(GameObject * owner)
		: owner(owner)
	{
		bulletPool = new ObjectPool<WarWeaponBullet>();
		muzzleFlash = new WarWeaponMuzzleFlash();
		firePos = new Transform();
		muzzlePos = new Transform();

	}
	Status update() override
	{
		auto player = GameObjectManager::Get()->GetPlayer();
		float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);

		owner->transform->rotation = rotation;
		FirePosUpdate();
		Fire();
		BulletUpdate();
		return Node::Status::Running;
	}
	void FirePosUpdate()
	{
		EnemyUnitAbstract * unit = static_cast<EnemyUnitAbstract*> (owner);

		firePos->position = unit->GetFirePosOffset();
		firePos->Rotate((float)D3DXToRadian(owner->transform->rotation));
		firePos->position += owner->transform->position;
		firePos->rotation = owner->transform->rotation;

		muzzlePos->position = unit->GetFirePosOffset();
		muzzlePos->Rotate((float)D3DXToRadian(owner->transform->rotation));
		muzzlePos->position += owner->transform->position;
		muzzlePos->rotation = owner->transform->rotation;
	}
	void initialize() override
	{
		currentShootDelay = 0;
		currentRepeatDelay = 0;
		currentShootCount = 0;
	}
	void Fire()
	{
		currentShootDelay += Time::Delta();
		if (currentShootDelay >= shootDelay)
		{
			currentRepeatDelay += Time::Delta();
			if (currentRepeatDelay >= repeatDelay)
			{
				currentRepeatDelay = 0;
				currentShootCount++;
				if (currentShootCount > shootCount)
				{
					currentShootCount = 0;
					currentShootDelay = 0;
				}
				if (activeBullets.size() >= bulletMaximum)
					return;
				auto bullet = bulletPool->AccquireObject();
				activeBullets.push_back(bullet);
				bullet->Fire(firePos);

				muzzleFlash->Flash(muzzlePos);
			}
		}
	}
	void BulletUpdate()
	{
		for (int i = 0; i < activeBullets.size(); i++)
		{
			float length = D3DXVec3Length(&(owner->transform->position - activeBullets[i]->transform->position));
			if (length >= bulletRange || activeBullets[i]->GetActive() == false)
			{
				bulletPool->ReleaseObject(activeBullets[i]);
				activeBullets.erase(activeBullets.begin() + i);
			}
		}
	}

private :
	GameObject * owner = nullptr;
	ObjectPool<WarWeaponBullet> * bulletPool = nullptr;
	vector<shared_ptr<WarWeaponBullet>> activeBullets;
	uint bulletMaximum = 50;
	uint bulletRange = 1000;
	WarWeaponMuzzleFlash * muzzleFlash = nullptr;
	float shootDelay = 1.5f;
	float currentShootDelay = 0;
	float repeatDelay = 0.1f;
	float currentRepeatDelay = 0;
	float currentShootCount = 0;
	float shootCount = 10;
	Transform * firePos = nullptr;
	Transform * muzzlePos = nullptr;
};

class IsActiveShield : public BrainTree::Decorator
{
public :
	Status update() override
	{
		float per = DxMath::ReliableRandom(0, 100);
		if (per < percentage)
			return Status::Success;
		return Status::Failure;
	}
private :
	float percentage = 30;
};

class IsExplosionState : public BrainTree::Decorator {
public :
	Status update() override
	{
		float per = DxMath::ReliableRandom(0, 100);
		if (per < percentage)
			return Status::Success;
		return Status::Failure;
	}
private:
	float percentage = 30;
};

class IsInOfChaseRange : public BrainTree::Decorator
{
public:
	IsInOfChaseRange(GameObject * owner)
		: owner(owner)
	{
	}

	Status update() override
	{
		EnemyUnitAbstract * enemy = static_cast<EnemyUnitAbstract*>(owner);
		auto player = GameObjectManager::Get()->GetPlayer();
		float dist = DxMath::GetDist(player->transform->position, enemy->transform->position);
		if (dist < enemy->GetEnoughCloseDist())
		{

			auto status = child->tick();
			return status;
		}
		return Status::Failure;
	}
private :
	GameObject * owner;
};

class IsActivePatternOne : public BrainTree::Decorator
{
public :
	Status update() override
	{

		return child->tick();
	}
};

class IsActivePatternTwo : public BrainTree::Decorator
{
public:
	Status update() override
	{
		return child->tick();
	}
};

class IsActivePatternThree : public BrainTree::Decorator
{
public:
	Status update() override
	{
		return child->tick();
	}
};