#pragma once

#include "EnemyUnit.h"
#include "GameObject/Projectiles/PlazmaElipseRedBullet.h"
#include "GameObject/Projectiles/PlazmaElipseRedMuzzleFlash.h"

class Medic : public EnemyUnit<PlazmaElipseRedBullet, PlazmaElipseRedMuzzleFlash>
{
public :
	Medic();


	virtual Vector3 GetFirePosOffset() override;
};