#include "stdafx.h"
#include "CricketBullet.h"

CricketBullet::CricketBullet()
	: Bullet(BulletInfo(2, 50), Vector3(50, 50, 1), Vector3(15, 15, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Ion_Red_Projectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
