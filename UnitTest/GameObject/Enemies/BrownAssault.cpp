#include "stdafx.h"
#include "BrownAssault.h"
#include "AI/FSM/EnemyState.h"
BrownAssault::BrownAssault()
	:EnemyUnit(ActorInfo(100, 70), Vector3(50, 50, 1))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Brown Assault.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 BrownAssault::GetFirePosOffset()
{
	return Vector3(10, 60, 0);
}
