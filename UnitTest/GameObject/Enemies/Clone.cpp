#include "stdafx.h"
#include "Clone.h"
#include "AI/FSM/EnemyState.h"
#include "Editor/DataGenerator.h"
Clone::Clone()
	: EnemyUnit(
		ActorInfo(
			CLONE_UNIT_DATA.maxHp, 
			CLONE_UNIT_DATA.moveSpeed),
		Vector3(
			CLONE_UNIT_DATA.size[0],
			CLONE_UNIT_DATA.size[1],
			CLONE_UNIT_DATA.size[2]))
{
	string path(CLONE_UNIT_DATA.texturePath);
	Texture2D *tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();

}

Vector3 Clone::GetFirePosOffset()
{
	return Vector3(10, 60, 0);
}
