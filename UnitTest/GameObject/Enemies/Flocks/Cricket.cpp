#include "stdafx.h"
#include "Cricket.h"
#include "Manager/FlockManager.h"
#include "GameObject/Actor.h"
#include "Game/Transform.h"
Cricket::Cricket()
	: EnemyFlock(ActorInfo(50, 100),Vector3(45, 90, 1), FlockManager::Get()->GetFlock("Cricket"))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/¬³ricket.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	FlockManager::Get()->PushFlock("Cricket", this);
}

Cricket::~Cricket()
{
}
