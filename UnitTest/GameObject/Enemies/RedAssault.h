#pragma once

#include "EnemyUnit.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "GameObject/Projectiles/IonBlueMuzzleFlash.h"

class RedAssault : public EnemyUnit<IonBlueBullet, IonBlueMuzzleFlash>
{
public :
	RedAssault();

	virtual Vector3 GetFirePosOffset() override;
};