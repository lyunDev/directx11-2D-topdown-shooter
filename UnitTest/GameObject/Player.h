#pragma once
#include "Game/GameObject.h"
#include "Utilities/ObjectPool.h"
#include "Actor.h"
#include "GameObject/MuzzleFlash.h"
#include "GameObject/Projectiles/Bullet.h"
#include "GameObject/Projectiles/NormalBullet.h"
#include "GameObject/Projectiles/NormalMuzzleFlash.h"
#include "GameObject/Projectiles/PlayerPlazmaBullet.h"
#include "GameObject/Projectiles/PlayerPlazmaMuzzleFlash.h"

class Player : public Actor
{
public :
	Player(Vector3 position, Vector3 size);
	~Player();
	virtual void Delete() override;

	virtual void OnUpdate() override;
	virtual void OnPostUpdate() override;
	virtual void OnCollisionStay(GameObject * other) override;
	virtual void OnCollisionEnter(GameObject * other) override;
	virtual void OnPostRender() override;
	
	virtual void Hit(float damage) override;

private :
	void PlayerMove();
	void PlayerRotate();
	void FirePosUpdate();
	void ShieldUpdate();

	void Fire();
	void BulletUpdate();
	void ActiveShield();

	void SlowUpdate();
	void BoostUpdate();
	void BulletRemoveSkill();
	void WideExplosionSkill();
	void LevelUp();

	void ChangeAttackMode();


private :
	float playerSpeed = 1000;


	Transform * firePos;
	Transform * muzzlePos;
	Transform *leftBoostPos;
	Transform * rightBoostPos;
	//class HPBar * hpBar;
	float fireRot;

	class Shield * shield;

	uint level = 0;
	uint maxLevel;
	float exp = 0;
	const vector<float> expTable = 
	{
		12, 
		300,
		600,
		1000,
		1500,
		2200,
		3000,
	};
private :

	ObjectPool<NormalBullet> * machineGunBulletPool;
	vector<shared_ptr<NormalBullet>> machineGunActiveBullets;
	uint machineGunBulletMaximum = 100;
	uint machineGunBulletRange = 1000;

	shared_ptr<NormalMuzzleFlash> machineGunMuzzleFlash;
	//class BoostEffect * leftBoostEffect;
//	class BoostEffect * rightBoostEffect;

	float machineGunShootDelay = 0.1f; // 0.2
	float machineGunCurrentShootDelay = 0;

private :
	ObjectPool<PlayerPlazmaBullet> * canonGunBulletPool;
	vector<shared_ptr<PlayerPlazmaBullet>> canonGunActiveBullets;
	uint canonGunBulletMaximum = 100;
	uint canonGunBulletRange = 1000;

	shared_ptr<PlayerPlazmaMuzzleFlash> canonGunMuzzleFlash;
	//class BoostEffect * leftBoostEffect;
//	class BoostEffect * rightBoostEffect;

	float canonGunShootDelay = 2.f; // 0.2
	float canonGunCurrentShootDelay = 0;


	float afterImageDelay = 0.1f;
	float currentAfterImageDelay = 0;

	bool leftMoveStop = false;
	bool rightMoveStop = false;
	bool upMoveStop = false;
	bool downMoveStop = false;

	class Transform * collisionTr;

	bool bActiveShield = false;
	float shieldEnergy = 10;

private :
	ID3D11ShaderResourceView * machineGunModeSRV;
	ID3D11ShaderResourceView * canonGunModeSRV;

	bool bMachineGunMode = true;


private: // gun mode ui
	class Pannel * machineGunUI = nullptr;
	class Pannel * canonGunUI = nullptr;
};