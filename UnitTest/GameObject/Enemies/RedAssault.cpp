#include "stdafx.h"
#include "RedAssault.h"
#include "AI/FSM/EnemyState.h"

RedAssault::RedAssault()
	: EnemyUnit(ActorInfo(100, 70), Vector3(50, 50, 1))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Red Assault.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 RedAssault::GetFirePosOffset()
{
	return Vector3(10, 60, 0);
}
