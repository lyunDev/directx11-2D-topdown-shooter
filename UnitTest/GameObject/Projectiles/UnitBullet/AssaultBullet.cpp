#include "stdafx.h"
#include "AssaultBullet.h"

#include "Editor/DataGenerator.h"
AssaultBullet::AssaultBullet()
	: Bullet(
		BulletInfo(
			ASSAULT_BULLET_DATA.damage,
			ASSAULT_BULLET_DATA.speed),
		Vector3(
			ASSAULT_BULLET_DATA.size[0],
			ASSAULT_BULLET_DATA.size[1],
			ASSAULT_BULLET_DATA.size[2]),
		Vector3(
			ASSAULT_BULLET_DATA.collisionSize[0],
			ASSAULT_BULLET_DATA.collisionSize[1],
			ASSAULT_BULLET_DATA.collisionSize[2]))
{

	//Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Plazma_Yellow_Projectile.png");
	string texturePath(ASSAULT_BULLET_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(texturePath));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);


}
