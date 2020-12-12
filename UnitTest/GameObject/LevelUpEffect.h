#pragma once
#include "Game/GameObject.h"

class LevelUpEffect : public GameObject
{
public :
	LevelUpEffect();


	virtual void OnUpdate() override;

	void LevelUp(Transform * ownerTr);
};