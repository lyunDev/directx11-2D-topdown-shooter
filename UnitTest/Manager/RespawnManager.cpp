#include "stdafx.h"
#include "RespawnManager.h"
#include "GameObject/TestEnemy.h"
#include "GameObject/WarMachine.h"
#include "Game/Transform.h"
#include "GameObject/Enemies/Clone.h"
#include <random>

#include "GameObject/Enemies/Assault.h"
#include "GameObject/Enemies/Cannoneer.h"
#include "GameObject/Enemies/Engineer.h"
#include "GameObject/Enemies/Medic.h"
#include "GameObject/Enemies/Nebulizer.h"
#include "GameObject/Enemies/Scout.h"
#include "GameObject/Enemies/Sniper.h"
#include "GameObject/Enemies/Tech.h"
#include "GameObject/Enemies/Flocks/Cricket.h"
#include "GameObject/Enemies/Flocks/Locust.h"
#include "GameObject/Enemies/Mutant.h"

#include <future>
#include <mutex>

RespawnManager::RespawnManager()
{
	//RespawnData<TestEnemy> * enemyRespawnData  = new RespawnData<TestEnemy>(4, 5);
	RespawnData<Clone> * cloneRespawnData = new RespawnData<Clone>(1, 5, 0, 60); // 1, 5, 0, 60,
	RespawnData<WarMachine> *  warMachineRespawnData = new RespawnData<WarMachine>(1, 1, 90, 150); // 1, 1, 90, 150
	RespawnData<Assault> *  assaultRespawnData = new RespawnData<Assault>(1, 2, 30, 120);
	RespawnData<Cannoneer> *  cannoneerRepawnData = new RespawnData<Cannoneer>(1, 1, 90, 150);
	RespawnData<Engineer> *  engineerRepawnData = new RespawnData<Engineer>(1, 2, 120, 150);
	//RespawnData<Medic> *  medicRepawnData = new RespawnData<Medic>(1, 3, 0, 1000);
	RespawnData<Nebulizer> *  nebulizerRepawnData = new RespawnData<Nebulizer>(1, 1, 120, 150);
	RespawnData<Sniper> *  sniperRepawnData = new RespawnData<Sniper>(1, 1, 120, 150);
	//RespawnData<Tech> *  techRepawnData = new RespawnData<Tech>(1, 2, 60, 90);
	RespawnData<Cricket> * cricketRespawnData = new RespawnData<Cricket>(1, 10, 60, 150);// 1, 10 , 60, 150
	RespawnData<Locust> * locustRespawnData = new RespawnData<Locust>(1, 10, 30, 150); // 1, 10, 30, 150

	RespawnData<Mutant> * mutantRespawnData = new RespawnData<Mutant>(1, 1, 150, 151);

	respawns.push_back(warMachineRespawnData);
	respawns.push_back(cricketRespawnData);
	respawns.push_back(cloneRespawnData);
	//respawns.push_back(locustRespawnData);
	
	respawns.push_back(sniperRepawnData);


	respawns.push_back(assaultRespawnData);
	respawns.push_back(cannoneerRepawnData);
	respawns.push_back(engineerRepawnData);
	//respawns.push_back(medicRepawnData);
	respawns.push_back(nebulizerRepawnData);

	//respawns.push_back(techRepawnData);


	respawns.push_back(mutantRespawnData);
	
	// dont des
}

RespawnManager::~RespawnManager()
{
}

void RespawnManager::Update()
{
	for (auto respawnData : respawns)
	{
		std::random_device rd; 
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> distr(-180.0, 180.0);

		Transform tr;
		tr.position = Vector3(WinMaxWidth / 2  + 300,0 , 0);
		tr.Rotate((float)D3DXToRadian(distr(gen)));
		Vector3 cameraPos = Camera::Get()->GetPos();
		cameraPos.x += WinMaxWidth / 2;
		cameraPos.y += WinMaxHeight / 2;
		tr.position += cameraPos;


		respawnData->Update(tr.position, distr(gen));
	}
}

