#include "stdafx.h"
#include "Assault.h"
#include "AI/FSM/EnemyState.h"
#include "Editor/DataGenerator.h"
Assault::Assault()
	: EnemyUnit(
		ActorInfo(
			ASSAULT_UNIT_DATA.maxHp, 
			ASSAULT_UNIT_DATA.moveSpeed),
		Vector3(
			ASSAULT_UNIT_DATA.size[0],
			ASSAULT_UNIT_DATA.size[1],
			ASSAULT_UNIT_DATA.size[2]))
{
	string path(ASSAULT_UNIT_DATA.texturePath);
	Texture2D *tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 Assault::GetFirePosOffset()
{
	return Vector3(10, 60, 0);
}
