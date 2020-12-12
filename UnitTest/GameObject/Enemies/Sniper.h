#pragma once
#include "EnemyUnit.h"
#include "GameObject/Projectiles/PlazmaArrowRedBullet.h"
#include "GameObject/Projectiles/PlazmaArrowRedMuzzleFlash.h"

class Sniper : public EnemyUnit<PlazmaArrowRedBullet, PlazmaArrowRedMuzzleFlash>
{
public :
	Sniper();

	virtual Vector3 GetFirePosOffset();


};