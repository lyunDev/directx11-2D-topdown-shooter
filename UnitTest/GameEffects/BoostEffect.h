#pragma once

#include "Game/GameObject.h"

class BoostEffect : public GameObject
{
public :
	BoostEffect();
	virtual ~BoostEffect();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
	void SetTr(Transform * tr);
private :
	class AlphaBuffer * alphaBuffer = nullptr;
};