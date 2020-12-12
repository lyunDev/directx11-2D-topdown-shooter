#include "stdafx.h"
#include "Engineer.h"
#include "AI/FSM/EnemyState.h"
#include "Editor/DataGenerator.h"
Engineer::Engineer()
	: EnemyUnit(
		ActorInfo(
			ENGINEER_UNIT_DATA.maxHp, 
			ENGINEER_UNIT_DATA.moveSpeed),
		Vector3(
			ENGINEER_UNIT_DATA.size[0],
			ENGINEER_UNIT_DATA.size[1],
			ENGINEER_UNIT_DATA.size[2]))
{
	string path(ENGINEER_UNIT_DATA.texturePath);
	Texture2D *tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	//SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 Engineer::GetFirePosOffset()
{
	return Vector3(19, 60, 0);
}
