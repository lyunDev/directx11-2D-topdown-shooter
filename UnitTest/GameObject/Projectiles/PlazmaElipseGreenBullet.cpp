#include "stdafx.h"
#include "PlazmaElipseGreenBullet.h"

PlazmaElipseGreenBullet::PlazmaElipseGreenBullet()
	: Bullet(BulletInfo(2, 100), Vector3(50, 40, 1), Vector3(40, 20, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/PlazmaElipse_Green_Projectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
