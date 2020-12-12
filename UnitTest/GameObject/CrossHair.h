#pragma once
#include "Game/GameObject.h"
class CrossHair : public GameObject
{
public :
	CrossHair();


protected :
	virtual void OnUpdate() override ;
};