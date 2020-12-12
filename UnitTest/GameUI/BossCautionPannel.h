#pragma once
#include "UI/Pannel.h"

class BossCautionPannel : public Pannel
{
public :
	BossCautionPannel();

	virtual void OnUpdate() override;

	void Caution();

private :
	// ±ôºý±ôºý 3¹ø ¹Ýº¹
	int loopingCount = 0;
	int maxLoopingCount = 3;
	bool isDecreaseAlpha = true;
	bool isStart = false;
};