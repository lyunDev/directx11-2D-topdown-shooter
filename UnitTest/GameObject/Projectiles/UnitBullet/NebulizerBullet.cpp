#include "stdafx.h"
#include "NebulizerBullet.h"
#include "Editor/DataGenerator.h"
NebulizerBullet::NebulizerBullet()
	: Bullet(
		BulletInfo(
			NEBULIZER_BULLET_DATA.damage,
			NEBULIZER_BULLET_DATA.speed),
		Vector3(
			NEBULIZER_BULLET_DATA.size[0],
			NEBULIZER_BULLET_DATA.size[1],
			NEBULIZER_BULLET_DATA.size[2]),
		Vector3(
			NEBULIZER_BULLET_DATA.collisionSize[0],
			NEBULIZER_BULLET_DATA.collisionSize[1],
			NEBULIZER_BULLET_DATA.collisionSize[2]))
{
	string path(NEBULIZER_BULLET_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
