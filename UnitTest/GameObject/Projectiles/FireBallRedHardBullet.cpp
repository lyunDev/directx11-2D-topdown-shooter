#include "stdafx.h"
#include "FireBallRedHardBullet.h"

FireBallRedHardBullet::FireBallRedHardBullet()
	: Bullet(BulletInfo(2, 100), Vector3(70, 100, 1), Vector3(30, 50, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/FireBall_Orange_HardProjectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
