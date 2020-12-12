#include "stdafx.h"
#include "PlazmaElipseRedBullet.h"

PlazmaElipseRedBullet::PlazmaElipseRedBullet()
	: Bullet(BulletInfo(2, 120), Vector3(50, 40, 1), Vector3(40, 20, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/PlazmaElipse_Red_Projectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);



	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
