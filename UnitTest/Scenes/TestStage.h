#pragma once
#include "GameObject/Player.h"
#include "GameObject/CrossHair.h"
#include "GameObject/FireBullet.h"
#include "GameObject/RespawnShip.h"
#include "GameObject/WarMachine.h"
#include "GameObject/Backgorund/BackgroundGenerator.h"
#include "AI/Flocking/Flock.h"

class TestStage : public IObject
{
public :
	// IObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void GUI() override;

private :
	 Player *  player = nullptr;
	 BackgroundGenerator * mapGen = nullptr;
	 CrossHair * crossHair = nullptr;

	// class Flock::Flock * flock;

};