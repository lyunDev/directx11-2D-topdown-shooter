#include "stdafx.h"
#include "Cannoneer.h"
#include "AI/FSM/EnemyState.h"
#include "Editor/DataGenerator.h"
Cannoneer::Cannoneer()
	: EnemyUnit(
		ActorInfo(
			CANNONEER_UNIT_DATA.maxHp, 
			CANNONEER_UNIT_DATA.moveSpeed),
		Vector3(
			CANNONEER_UNIT_DATA.size[0],
			CANNONEER_UNIT_DATA.size[1],
			CANNONEER_UNIT_DATA.size[2]))
{
	string path(CANNONEER_UNIT_DATA.texturePath);
	Texture2D *tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	//SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 Cannoneer::GetFirePosOffset()
{
	return Vector3(10, 130, 0);
}
