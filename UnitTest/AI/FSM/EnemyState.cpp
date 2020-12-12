#include "stdafx.h"
#include "EnemyState.h"
#include "Game/GameObjectManager.h"
#include "Game/Transform.h"
#include "GameObject/Enemies/EnemyUnit.h"
#include <random>
namespace EnemyAI
{

	// Thinking State ------------------------------------------------------------
	void ThinkingState::Enter(GameObject * owner)
	{

	}

	FSMState * ThinkingState::Update(GameObject * owner)
	{
		EnemyUnitAbstract * enemy = static_cast<EnemyUnitAbstract *>(owner);

		GameObject * player = GameObjectManager::Get()->GetPlayer();

		if (player == nullptr) return nullptr;

		float dist = DxMath::GetDist(player->transform->position, enemy->transform->position);
		if (dist > enemy->GetEnoughCloseDist())
		{

			return new MovingState();
		}
		else
		{
			return new AttackState();
		}
		return nullptr;
	}

	void ThinkingState::Exit(GameObject * owner)
	{

	}



	// MovingState ---------------------------------------------------------
	void MovingState::Enter(GameObject * owner)
	{
		GameObject * player = GameObjectManager::Get()->GetPlayer();
		if (player == nullptr) return;

		//float speed = owner->GetMoveSpeed() * Time::Delta();
		float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);

		//rotation += distr(gen);

		//Transform tr;
		//tr.position = Vector3(0, speed, 0);
		//tr.Rotate((float)D3DXToRadian(rotation));
		//owner->transform->position += tr.position;
		owner->transform->rotation = rotation;
		moveRot = rotation;
	}

	FSMState * MovingState::Update(GameObject * owner)
	{
		EnemyUnitAbstract * enemy = static_cast<EnemyUnitAbstract *>(owner);

		GameObject * player = GameObjectManager::Get()->GetPlayer();
		if (player == nullptr) return nullptr;



		float speed = enemy->GetMoveSpeed() * Time::Delta();
		//float rotation = owner->transform->rotation;
		float dist = DxMath::GetDist(player->transform->position, owner->transform->position);

		// 일정거리 안에 있으면 이동방향 고정
		if (dist < enemy->GetChaseDist())
		{
			Transform tr;
			tr.position = Vector3(0, speed, 0);
			tr.Rotate((float)D3DXToRadian(moveRot));
			owner->transform->position += tr.position;

			float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);
			owner->transform->rotation = rotation;
		}
		else // 일정거리 밖에 있으면 똑바로 추적
		{
			Transform tr;
			tr.position = Vector3(0, speed, 0);
			tr.Rotate((float)D3DXToRadian(owner->transform->rotation));
			owner->transform->position += tr.position;

			float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);
			owner->transform->rotation = rotation;
			moveRot = rotation;
		}

		/*if (dist > enemy->GetEnoughCloseDist() && dist < enemy->GetChaseDist())
		{

			return nullptr;
		}
		else
			return new ThinkingState();*/
		if (dist > enemy->GetEnoughCloseDist())
		{
			return nullptr;
		}
		else
			return new ThinkingState();
	}

	void MovingState::Exit(GameObject * owner)
	{

	}


	// AttackState --------------------------------------------------------
	void AttackState::Enter(GameObject * owner)
	{
	}

	FSMState * AttackState::Update(GameObject * owner)
	{
		EnemyUnitAbstract * enemy = static_cast<EnemyUnitAbstract *>(owner);

		GameObject * player = GameObjectManager::Get()->GetPlayer();
		if (player == nullptr) return nullptr;

		float dist = DxMath::GetDist(player->transform->position, enemy->transform->position);


		float rotation = DxMath::GetAngle(Values::UpVec, player->transform->position - owner->transform->position);
		owner->transform->rotation = rotation;

		if (dist > enemy->GetEnoughCloseDist())
		{
			return new ThinkingState();
		}
		return nullptr;
	}

	void AttackState::Exit(GameObject * owner)
	{
	}

	void DiyingState::Enter(GameObject * owner)
	{
	}

	FSMState * DiyingState::Update(GameObject * owner)
	{
		return nullptr;
	}

	void DiyingState::Exit(GameObject * owner)
	{
	}
}