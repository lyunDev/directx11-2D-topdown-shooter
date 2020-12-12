#pragma once
#include "Game/GameObject.h"

class FireBullet : public GameObject
{
public :
	FireBullet();

	virtual void OnUpdate() override;
	void Fire(Transform fireTr);
	bool isHited = false;

private :
	Transform * collisionTr = nullptr;
	float bulletSpd = 1000;
};

