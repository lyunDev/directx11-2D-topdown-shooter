#include "stdafx.h"
#include "GasGreenBullet.h"

GasGreenBullet::GasGreenBullet()
	: Bullet(BulletInfo(2, 130), Vector3(30, 100, 1), Vector3(15, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Gas_Green_Projectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
