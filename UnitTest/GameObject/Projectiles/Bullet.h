#pragma once
#include "Game/GameObject.h"
struct BulletInfo
{
	BulletInfo(float damage, float bulletSpd)
		: damage(damage), bulletSpd(bulletSpd)
	{
	}
	float damage; // default 10
	float bulletSpd; // default 1000
};

class Bullet : public GameObject
{
public:
	Bullet(BulletInfo bulletInfo, Vector3 objectSize, Vector3 collisionSize);



	virtual void OnUpdate() override;
	void Fire(Transform * fireTr);
	virtual void OnCollisionEnter(GameObject* other) override;

	virtual void OnEnable() override;
	virtual void OnDisable() override;
	BulletInfo GetBulletInfo() 
	{
		return bulletInfo;
	}
	void SetBulletInfo(BulletInfo info)
	{
		bulletInfo = info;
	}
	void SetLifeTime(float lifeTime)
	{
		this->lifeTime = lifeTime;
	}
	void Explosion()
	{

	}
private :
	float lifeTime = 10.0f;
	float currentLiftTime =0.0f;
private:
	Transform * collisionTr;
	BulletInfo bulletInfo;
};