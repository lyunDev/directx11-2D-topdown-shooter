#pragma once
#include "Game/GameObject.h"
#include "UI/Pannel.h"
class BossHPBar : public Pannel
{
public :
	BossHPBar();
	virtual ~BossHPBar();


	virtual void OnUpdate() override;
};