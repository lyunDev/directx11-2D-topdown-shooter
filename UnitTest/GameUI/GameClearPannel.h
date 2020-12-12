#pragma once
#include "UI/Pannel.h"

class GameClearPannel : public Pannel
{
public :
	GameClearPannel();

	virtual void OnUpdate() override;

	void Clear(function<void(void)> onCompleted);

private :
	float currentDelay = 0;
	float sceneTransitionDelay = 2;
	function<void(void)> onCompleted;
};