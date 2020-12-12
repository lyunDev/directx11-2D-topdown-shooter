#include "stdafx.h"
#include "Scout.h"
#include "AI/FSM/EnemyState.h"

Scout::Scout()
	: EnemyUnit(ActorInfo(100, 100), Vector3(70, 70, 1))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Scout.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 Scout::GetFirePosOffset()
{
	return Vector3(10, 60, 0);
}
