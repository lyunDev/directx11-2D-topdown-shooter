#pragma once
#include "AI/Flocking/FlockAgent.h"
#include "GameObject/Actor.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "GameObject/Enemies/Flocks/EnemyFlock.h"
#include "GameObject/Projectiles/BlueSwirl.h"
#include "GameObject/Projectiles/LocustBullet.h"
class Locust : public EnemyFlock<LocustBullet>
{
public :
	Locust();
	virtual ~Locust();
};