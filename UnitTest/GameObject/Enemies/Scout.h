#pragma once
#include "EnemyUnit.h"
#include "GameObject/Projectiles/IonRedBullet.h"
#include "GameObject/Projectiles/IonRedMuzzleFlash.h"

class Scout : public EnemyUnit<IonRedBullet, IonRedMuzzleFlash>
{
public :
	Scout();

	virtual Vector3 GetFirePosOffset() override;
};