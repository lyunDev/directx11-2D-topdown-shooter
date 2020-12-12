#pragma once
#include "Game/GameObject.h"

class ExplosionEffect : public GameObject
{
public :
	ExplosionEffect();


	virtual void OnUpdate() override;
	

	void SetTr(Transform tr);

private:

};