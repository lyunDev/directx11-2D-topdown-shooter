#include "stdafx.h"
#include "Sniper.h"
#include "AI/FSM/EnemyState.h"
#include "Editor/DataGenerator.h"
Sniper::Sniper()
	: EnemyUnit(
		ActorInfo(
			SNIPER_UNIT_DATA.maxHp,
			SNIPER_UNIT_DATA.moveSpeed),
		Vector3(
			SNIPER_UNIT_DATA.size[0],
			SNIPER_UNIT_DATA.size[1],
			SNIPER_UNIT_DATA.size[2]))
{
	string path(SNIPER_UNIT_DATA.texturePath);
	Texture2D *tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	//SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 Sniper::GetFirePosOffset()
{
	return Vector3(-5, 80, 0);
}
