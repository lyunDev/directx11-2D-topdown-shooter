#pragma once
#include "EnemyUnit.h"
#include "GameObject/Projectiles/PlazmaElipseGreenBullet.h"
#include "GameObject/Projectiles/PlazmaElipseGreenMuzzleFlash.h"

class Engineer : public EnemyUnit<PlazmaElipseGreenBullet, PlazmaElipseGreenMuzzleFlash>
{
public :
	Engineer();

	virtual Vector3 GetFirePosOffset() override;
};