#include "stdafx.h"
#include "PlazmaArrowRedBullet.h"

PlazmaArrowRedBullet::PlazmaArrowRedBullet()
	: Bullet(BulletInfo(2, 300), Vector3(30, 70, 1), Vector3(15, 50, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/PlazmaArrow_Red_Projectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
