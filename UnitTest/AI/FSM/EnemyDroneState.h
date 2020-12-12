#pragma once
#include "FSMState.h"
#include "EnemyState.h"

class GameObject;

namespace EnemyDroneAI
{
	class MovingState : public EnemyState
	{
	public:
		// EnemyState을(를) 통해 상속됨
		virtual void Enter(GameObject * owner) override;
		virtual FSMState * Update(GameObject * owner) override;
		virtual void Exit(GameObject * owner) override;

	private:
		float moveRot = 0;
	};

	class ThinkingState : public  EnemyState
	{
	public:
		// EnemyState을(를) 통해 상속됨
		virtual void Enter(GameObject * owner) override;
		virtual FSMState * Update(GameObject * owner) override;
		virtual void Exit(GameObject * owner) override;
	};

	class AttackState : public  EnemyState
	{
	public:
		// EnemyState을(를) 통해 상속됨
		virtual void Enter(GameObject * owner) override;
		virtual FSMState * Update(GameObject * owner) override;
		virtual void Exit(GameObject * owner) override;
	};
	class DiyingState : public  EnemyState
	{
	public:
		// EnemyState을(를) 통해 상속됨
		virtual void Enter(GameObject * owner) override;
		virtual FSMState * Update(GameObject * owner) override;
		virtual void Exit(GameObject * owner) override;
	};
}