#pragma once
#include "Game/GameObject.h"
#include "Utilities/Layers.h"
class Explosion : public GameObject
{
public :
	Explosion(Vector3 size);

	virtual void OnUpdate() override;
	virtual void OnEnable() override;
	virtual void OnDisable() override;
	void Explode(Transform * explodeTr);


private :
	bool isAnimCompleted = false;
};