#pragma once


#include "EnemyUnit.h"
#include "GameObject/Projectiles/GasGreenBullet.h"
#include "GameObject/Projectiles/GasGreenMuzzleFlash.h"

class Tech : public EnemyUnit<GasGreenBullet, GasGreenMuzzleFlash>
{
public :
	Tech();

	virtual Vector3 GetFirePosOffset() override;
};