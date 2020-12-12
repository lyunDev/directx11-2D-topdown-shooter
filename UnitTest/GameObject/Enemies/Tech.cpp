#include "stdafx.h"
#include "Tech.h"
#include "AI/FSM/EnemyState.h"

Tech::Tech()
	: EnemyUnit(ActorInfo(100, 100), Vector3(100, 100 ,1))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Tech.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	//SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 Tech::GetFirePosOffset()
{
	return Vector3(15, 60, 0);
}
