#include "stdafx.h"
#include "Nebulizer.h"
#include "AI/FSM/EnemyState.h"
#include "Editor/DataGenerator.h"
Nebulizer::Nebulizer()
	: EnemyUnit(
		ActorInfo(
			NEBULIZER_UNIT_DATA.maxHp,
			NEBULIZER_UNIT_DATA.moveSpeed),
		Vector3(
			NEBULIZER_UNIT_DATA.size[0],
			NEBULIZER_UNIT_DATA.size[1],
			NEBULIZER_UNIT_DATA.size[2]))
{
	string path(NEBULIZER_UNIT_DATA.texturePath);
	Texture2D *tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	//SetRenderToCollisionBox(true);

	enemyState = new EnemyAI::ThinkingState();
}

Vector3 Nebulizer::GetFirePosOffset()
{
	return Vector3(2, 60, 1);
}
