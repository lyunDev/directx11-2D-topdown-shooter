#pragma once
#include "Game/GameObject.h"


class ScoreItem : public GameObject
{
public :
	ScoreItem();

private :
	bool isMagnetState = false;
};