#pragma once
#include "Game/GameObject.h"


class Shield : public GameObject
{
public :
	Shield(GameObject * owner,Vector3 size, float energyMax);
	virtual void OnUpdate() override;

	void ActiveShield();
	void HitShield(float damage);
private :
	float healingEnergy = 1;
	float currentEnergy = 0;
	float energyMax = 0;
	float currentAlpha = 1;
	GameObject * owner;
};
