#pragma once
#include "Bullet.h"

class PlayerPlazmaBullet : public Bullet
{
public :
	PlayerPlazmaBullet();

	virtual void OnCollisionEnter(GameObject* other);
	
};