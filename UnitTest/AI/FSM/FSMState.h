#pragma once
#include "Game/GameObject.h"

class FSMState
{
public :
	virtual void Enter(GameObject * owner) {};
	// 만약 상태 전이가 필요하다면 해당 state 반환
	// 전이가 필요없다면 nullptr 반환
	virtual FSMState * Update(GameObject * owner) { return nullptr; };
	virtual void Exit(GameObject * owner) {};
};