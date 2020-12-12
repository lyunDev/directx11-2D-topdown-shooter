#include "stdafx.h"
#include "CannoneerBullet.h"
#include "Editor/DataGenerator.h"
CannoneerBullet::CannoneerBullet() 
	: Bullet(
		BulletInfo(
			CANNONEER_BULLET_DATA.damage,
			CANNONEER_BULLET_DATA.speed),
		Vector3(
			CANNONEER_BULLET_DATA.size[0],
			CANNONEER_BULLET_DATA.size[1],
			CANNONEER_BULLET_DATA.size[2]),
		Vector3(
			CANNONEER_BULLET_DATA.collisionSize[0],
			CANNONEER_BULLET_DATA.collisionSize[1],
			CANNONEER_BULLET_DATA.collisionSize[2]))
{
	string path(CANNONEER_BULLET_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
