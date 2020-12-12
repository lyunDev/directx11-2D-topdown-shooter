#include "stdafx.h"
#include "Locust.h"
#include "Manager/FlockManager.h"
Locust::Locust()
	: EnemyFlock(ActorInfo(30, 100), Vector3(40, 60, 1), FlockManager::Get()->GetFlock("Locust"))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Locust.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	FlockManager::Get()->PushFlock("Locust", this);
}

Locust::~Locust()
{
}
