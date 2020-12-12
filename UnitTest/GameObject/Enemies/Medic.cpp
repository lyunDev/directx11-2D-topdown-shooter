#include "stdafx.h"
#include "Medic.h"
#include "AI/FSM/EnemyState.h"

Medic::Medic()
	: EnemyUnit(ActorInfo(100, 100), Vector3(70, 70, 1))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Medic.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	//SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();

}

Vector3 Medic::GetFirePosOffset()
{
	return Vector3(5, 60, 0);
}
