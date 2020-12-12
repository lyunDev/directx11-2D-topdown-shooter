#pragma once

#include "EnemyUnit.h"
#include "GameObject/Projectiles/PlazmaYellowBullet.h"
#include "GameObject/Projectiles/PlazmaYellowMuzzleFlash.h"

class Assault : public EnemyUnit<PlazmaYellowBullet, PlazmaYellowMuzzleFlash>
{
public :
	Assault();

	virtual Vector3 GetFirePosOffset() override;
};