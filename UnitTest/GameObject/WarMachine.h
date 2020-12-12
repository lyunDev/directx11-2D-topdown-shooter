#pragma once

#include "Actor.h"

#include "Utilities/ObjectPool.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "Game/Transform.h"
#include "GameObject/Projectiles/BlueSwirl.h"
enum class WarMachineType
{
	Light_1 = 0,
	Light_2,
	Light_3,
	Light_4,
	Light_5,
	Heavy_1,
	Heavy_2,
	Heavy_3,
};
enum class WarWeaponType
{
	Gun1_1 = 0,
	Gun1_2,
	Gun1_3,
	Gun1_4,
	Gun2,
	Gun3_1,
	Gun3_2
};
class WarWeapon;
class WarMachine : public Actor
{
public :
	//WarMachine(Vector3 position, Vector3 size, WarMachineType warMachineType, WarWeaponType warWeaponType);
	WarMachine();
	~WarMachine();

	virtual void OnCollisionEnter(GameObject * other) override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnPostRender() override;

	virtual void OnRespawn(Vector3 respawnPos, float respawnRot) override;

	virtual void Hit(float damage) override;

private :
	void Fire();
	void BulletUpdate();

	WarMachineType warMachineType;
	WarWeaponType warWeaponType;

private :
	shared_ptr< WarWeapon> warWeapon;


private : // about bullet
	ObjectPool<BlueSwirl> * bulletPool = nullptr;
	vector<shared_ptr<BlueSwirl>> activeBullets;
	uint bulletMaximum = 200;
	uint bulletRange = 1000;
	float shootDelay = 2;
	float currentShootDelay = 0;
	vector<Transform> firePoses;
	int rotOffset = 0;
};