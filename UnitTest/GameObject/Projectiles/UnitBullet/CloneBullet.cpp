#include "stdafx.h"
#include "CloneBullet.h"
#include "Editor/DataGenerator.h"

CloneBullet::CloneBullet()
	: Bullet(
		BulletInfo(
			CLONE_BULLET_DATA.damage, 
			CLONE_BULLET_DATA.speed),
		Vector3(
			CLONE_BULLET_DATA.size[0],
			CLONE_BULLET_DATA.size[1],
			CLONE_BULLET_DATA.size[2]),
		Vector3(
			CLONE_BULLET_DATA.collisionSize[0],
			CLONE_BULLET_DATA.collisionSize[1],
			CLONE_BULLET_DATA.collisionSize[2]))
{
	string path(CLONE_BULLET_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	SetRenderToCollisionBox(true);
}
