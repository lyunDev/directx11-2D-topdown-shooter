#include "stdafx.h"
#include "WarWeaponBullet.h"

WarWeaponBullet::WarWeaponBullet()
	: Bullet(BulletInfo(4, 500), Vector3(30, 200, 1), Vector3(10, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/NormalBullet.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	SetRenderToCollisionBox(true);
}
