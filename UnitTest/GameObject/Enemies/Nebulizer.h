#pragma once

#include "EnemyUnit.h"
#include "GameObject/Projectiles/PlazmaYellowBullet.h"
#include "GameObject/Projectiles/PlazmaYellowMuzzleFlash.h"

class Nebulizer : public EnemyUnit<PlazmaYellowBullet, PlazmaYellowMuzzleFlash>
{
public :
	Nebulizer(); 

	virtual Vector3 GetFirePosOffset() override;
};