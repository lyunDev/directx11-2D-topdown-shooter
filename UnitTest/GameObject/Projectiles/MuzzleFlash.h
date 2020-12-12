#pragma once
#include "Game/GameObject.h"

class MuzzleFlash : public GameObject
{
public:
	MuzzleFlash(Vector3 size);

	virtual void OnUpdate() override;
	virtual void OnDisable() override;
	void Flash(Transform * fireTr);
};