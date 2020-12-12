#pragma once
#include "Game/GameObject.h"
#include "GameObject/WarMachine.h"
#include "Utilities/ObjectPool.h"
#include "Actor.h"
#include "GameObject/Projectiles/WarWeaponBullet.h"
#include "GameObject/Projectiles/WarWeaponMuzzleFlash.h"


class WarWeapon : public Actor
{
public :
	WarWeapon(Vector3 position, Vector3 size, WarWeaponType warWeaponType);
	virtual ~WarWeapon();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnPostRender() override;
	virtual void OnCollisionEnter(GameObject * other) override;
	virtual void OnRespawn(Vector3 respawnPos, float respawnRot);

	virtual void Hit(float damage) override;
private :

	void FirePosUpdate();
	void Fire();
	void BulletUpdate();

private:
	WarWeaponType warWeaponType;
	Vector3 fixedPos;

	GameObject* player = nullptr;

private : // about bullet 
	ObjectPool<WarWeaponBullet> * bulletPool = nullptr;
	vector<shared_ptr<WarWeaponBullet>> activeBullets;
	uint bulletMaximum = 50;
	uint bulletRange = 1000;
	class WarWeaponMuzzleFlash * muzzleFlash = nullptr;
	float shootDelay = 2;
	float currentShootDelay = 0;

	float rpm = 0.1f;
	float currentRpm = 0;
	float currentShootCount = 0;
	float shootCount = 10;
	Transform * firePos = nullptr;
	Transform * muzzlePos = nullptr; 

private :

	//class ColorBuffer * colorBuffer = nullptr;
	//class DissolveBuffer * dissolveBuffer = nullptr;
	//ID3D11ShaderResourceView * dissolveMap = nullptr;
};