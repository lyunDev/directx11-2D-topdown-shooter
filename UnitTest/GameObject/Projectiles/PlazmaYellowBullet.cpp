#include "stdafx.h"
#include "PlazmaYellowBullet.h"

PlazmaYellowBullet::PlazmaYellowBullet()
	: Bullet(BulletInfo(2, 150), Vector3(60, 100, 1), Vector3(15, 30, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Plazma_Yellow_Projectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
