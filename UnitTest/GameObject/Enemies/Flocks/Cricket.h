#pragma once
#include "AI/Flocking/FlockAgent.h"
#include "GameObject/Actor.h"
#include "GameObject/Enemies/Flocks/EnemyFlock.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "GameObject/Projectiles/BlueSwirl.h"
#include "GameObject/Projectiles/CricketBullet.h"

class Cricket : public EnemyFlock<CricketBullet>
{
public :
	Cricket();
	virtual ~Cricket();
private :

};