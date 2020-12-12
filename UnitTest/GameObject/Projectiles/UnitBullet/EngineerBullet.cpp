#include "stdafx.h"
#include "EngineerBullet.h"
#include "Editor/DataGenerator.h"
EngineerBullet::EngineerBullet()
	: Bullet(
		BulletInfo(
			ENGINEER_BULLET_DATA.damage,
			ENGINEER_BULLET_DATA.speed),
		Vector3(
			ENGINEER_BULLET_DATA.size[0],
			ENGINEER_BULLET_DATA.size[1],
			ENGINEER_BULLET_DATA.size[2]),
		Vector3(
			ENGINEER_BULLET_DATA.collisionSize[0],
			ENGINEER_BULLET_DATA.collisionSize[1],
			ENGINEER_BULLET_DATA.collisionSize[2]))
{
	string path(ENGINEER_BULLET_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}