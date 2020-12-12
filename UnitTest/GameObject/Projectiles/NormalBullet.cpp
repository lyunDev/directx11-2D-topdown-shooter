#include "stdafx.h"
#include "NormalBullet.h"

NormalBullet::NormalBullet()
	: Bullet(BulletInfo(10, 1000), Vector3(30, 200, 1), Vector3(10, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/NormalBullet.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::PLAYER_BULLET);
	SetRenderToCollisionBox(true);
}


