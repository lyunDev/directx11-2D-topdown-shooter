#pragma once
#include "Actor.h"
#include "Game/GameObject.h"
#include "Utilities/ObjectPool.h"
#include "GameObject/Projectiles/Bullet.h"


class TestEnemy : public Actor
{
public :
	TestEnemy(Vector3 position, Vector3 size);
	TestEnemy();
	virtual ~TestEnemy();

	virtual void OnCollisionEnter(GameObject* other) override;
	virtual void OnUpdate() override;
	virtual void OnPreRender() override;
	virtual void OnRender() override;
	virtual void OnPostRender() override;

	virtual void OnRespawn(Vector3 respawnPos, float respawnRot) override;


	float GetEnoughCloseDist()
	{
		return enoughCloseDist;
	}
	float GetChanseDist()
	{
		return chaseDist;
	}
	float GetMoveSpeed()
	{
		return moveSpeed;
	}
private : // about bullet
	void FirePosUpdate();
	void Fire();
	void BulletUpdate();

private :

	ID3D11ShaderResourceView * dissolveMap = nullptr;
	class DissolveBuffer * dissolveBuffer = nullptr;

	class ColorBuffer * colorBuffer = nullptr;


	float chaseDist = 2000;
	float enoughCloseDist = 300;
	float moveSpeed = 100;

	class EnemyState * enemyState;

private :
	ObjectPool<Bullet> * bulletPool = nullptr;
	vector<shared_ptr<Bullet>> activeBullets;
	uint bulletMaximum = 5;
	uint bulletRange = 1000;
	class MuzzleFlash * muzzleFlash = nullptr;
	float shootDelay = 0.5f;
	float currentShootDelay = 0;

	Transform * firePos = nullptr;
	Transform * muzzlePos = nullptr;


};