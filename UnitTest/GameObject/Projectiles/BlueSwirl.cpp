#include "stdafx.h"
#include "BlueSwirl.h"

BlueSwirl::BlueSwirl()
	: Bullet(BulletInfo(5, 80), Vector3(50, 50, 1), Vector3(15, 15, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/BlueSwirl.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::ENEMY_BULLET);
	//SetRenderToCollisionBox(true);
}
