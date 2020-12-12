#pragma once
#include "EnemyUnit.h"
#include "GameObject/Projectiles/FireBallRedHardBullet.h"
#include "GameObject/Projectiles/FireBallRedMuzzleFlash.h"


class Cannoneer : public EnemyUnit<FireBallRedHardBullet, FireBallRedMuzzleFlash>
{
public :
	Cannoneer();

	virtual Vector3 GetFirePosOffset() override;
};