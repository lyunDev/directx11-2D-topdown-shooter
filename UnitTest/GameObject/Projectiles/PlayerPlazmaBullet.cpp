#include "stdafx.h"
#include "PlayerPlazmaBullet.h"
#include "GameEffects/PlayerPlazmaExplosion.h"
#include "Game/GameObjectManager.h"
#include "GameObject/Actor.h"
PlayerPlazmaBullet::PlayerPlazmaBullet()
	: Bullet(BulletInfo(50, 200), Vector3(100, 130, 1), Vector3(50, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Plazma_Violent_Projectile.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetObjectLayer(ObjectLayer::PLAYER_BULLET);
	SetRenderToCollisionBox(true);
}

void PlayerPlazmaBullet::OnCollisionEnter(GameObject * other)
{
	Bullet::OnCollisionEnter(other);
	PlayerPlazmaExplosion * explosion = new PlayerPlazmaExplosion();
	explosion->Explode(transform);
	Camera::Get()->Shake(0.5f, 5.0f);
	auto enemies = GameObjectManager::Get()->FindObjectsWithDistance(this, 150, ObjectLayer::ENEMY);
	for (auto enemy : enemies)
	{
		Actor * actor = static_cast<Actor*>(enemy);
		assert(actor != nullptr);
		actor->Hit(GetBulletInfo().damage);
	}
}
