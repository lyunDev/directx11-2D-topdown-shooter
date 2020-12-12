#pragma once
#include "EnemyUnit.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "GameObject/Projectiles/IonBlueMuzzleFlash.h"

class Pyro : public EnemyUnit<IonBlueBullet, IonBlueMuzzleFlash>
{
public :
	Pyro();
	virtual Vector3 GetFirePosOffset() override;
};