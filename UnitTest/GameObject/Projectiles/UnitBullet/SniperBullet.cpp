#include "stdafx.h"
#include "SniperBullet.h"
#include "Editor/DataGenerator.h"
SniperBullet::SniperBullet()
	: Bullet(
		BulletInfo(
			SNIPER_BULLET_DATA.damage,
			SNIPER_BULLET_DATA.speed),
		Vector3(
			SNIPER_BULLET_DATA.size[0],
			SNIPER_BULLET_DATA.size[1],
			SNIPER_BULLET_DATA.size[2]),
		Vector3(
			SNIPER_BULLET_DATA.collisionSize[0],
			SNIPER_BULLET_DATA.collisionSize[1],
			SNIPER_BULLET_DATA.collisionSize[2]))
{
	string path(SNIPER_BULLET_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
