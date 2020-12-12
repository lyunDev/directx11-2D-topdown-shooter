#pragma once
#include "EnemyUnit.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "GameObject/Projectiles/IonBlueMuzzleFlash.h"

class Clone : public EnemyUnit<IonBlueBullet, IonBlueMuzzleFlash>
{
public :
	Clone();

	virtual Vector3 GetFirePosOffset() override;
};