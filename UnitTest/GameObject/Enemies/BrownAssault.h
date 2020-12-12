#pragma once

#include "EnemyUnit.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "GameObject/Projectiles/IonBlueMuzzleFlash.h"

class BrownAssault : public EnemyUnit<IonBlueBullet, IonBlueMuzzleFlash>
{
public :
	BrownAssault();

	virtual Vector3 GetFirePosOffset() override;
};