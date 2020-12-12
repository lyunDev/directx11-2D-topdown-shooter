#pragma once
#include "FSMState.h"


class GameObject;

class EnemyState : public  FSMState
{
public:

	virtual void Enter(GameObject * owner) override {};
	// 만약 상태 전이가 필요하다면 해당 state 반환
	// 전이가 필요없다면 nullptr 반환
	virtual FSMState * Update(GameObject * owner) override { return nullptr; };
	virtual void Exit(GameObject * owner) override {};

};
namespace EnemyAI
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