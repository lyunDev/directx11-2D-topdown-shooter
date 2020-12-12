#pragma once
#include "UI/Pannel.h"

class FadeInOut : public Pannel
{
public :
	FadeInOut();
	virtual void OnUpdate() override;

	void FadeIn(function<void(void)> fadeInCompleted);
	void FadeOut(function<void(void) >fadeOutCompleted);

private:
	function<void(void)>fadeInCompleted;
	function<void(void)> fadeOutCompleted;
	bool isFadeIn = false;
};