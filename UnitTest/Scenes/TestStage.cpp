#include "Framework.h"
#include "TestStage.h"
#include "Geometries/TextureRect.h"
#include "GameObject/Player.h"
#include "GameObject/TestEnemy.h"
#include "GameObject/CrossHair.h"

#include "Game/GameObjectManager.h"
#include "Game/GameObject.h"
#include "Game/RenderManager.h"

//#include "AI/Box.h"
//#include "AI/Flock.h"
#include "GameObject/Drone.h"
#include "Manager/RespawnManager.h"
#include "Manager/FlockManager.h"
#include "Manager/EventManager.h"

#include "GameObject\Backgorund\SciFiBg.h"

#include "UI/Button.h"
#include "UI/Pannel.h"

#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"
#include "GameUI/FadeInOut.h"

#include "Editor/DataGenerator.h"
#include "GameUI/PlayerHPBar.h"
//#include "AI/Flocking/Flock.h"

void TestStage::Init()
{

	Camera::Create();
	GameObjectManager::Create();
	RenderManager::Create();
	FlockManager::Create();
	EventManager::Create();
	FadeInOut * fadeOut = new FadeInOut();
	fadeOut->FadeOut([]()
	{
		FadeInOut * fadeIn = new FadeInOut();
		fadeIn->FadeIn([]()
		{

		});
	});





	DataGenerator generator;
	generator.ReadUnitBullet();
	generator.ReadUnitData();
	generator.ReadUnitMuzzleFlash();
	generator.ReadUnitRespawn();

	player = new Player(Vector3(WinMaxWidth / 2, WinMaxHeight / 2, 0), Vector3(100, 100, 1));
	RespawnManager::Create();
	crossHair = new CrossHair();
	mapGen = new BackgroundGenerator();
	mapGen->Init<SciFiBg>(Vector3(WinMaxWidth * 0.5f, WinMaxHeight * 0.5f, 0));




	Button * button = new Button(TexturePath + L"UI/Menu_BTN.png", Vector3(WinMaxWidth - 50, WinMaxHeight -50, 0), Vector3(60, 60, 1), []()
	{
		EventDispatcher::TriggerEvent(SceneEvent::Transition + "MainScene");
	});
	//Pannel * pannel2 = new Pannel(TexturePath + L"UI/Fill.png", Vector3(WinMaxWidth / 2, WinMaxHeight - 30, 0), Vector3(WinMaxWidth / 2 - 47, 35, 1), false);
	Pannel * skillBar = new Pannel(TexturePath + L"UI/Skillbar_Back222.png", Vector3(WinMaxWidth * 0.5f, 70, 0), Vector3(500, 75, 1), false);
	//Pannel * Machingun = new Pannel(TexturePath + L"UI/heavygun.png", Vector3(WinMaxWidth - 130, 150, 0), Vector3(150, 200, 1), false);
	//Pannel * luncher = new Pannel(TexturePath + L"UI/luncher.png", Vector3(WinMaxWidth - 130, 150, 0), Vector3(150, 200, 1), false);
	
	//Pannel * hpBar = new Pannel(TexturePath + L"UI/HealthBarFill.png", Vector3(250, WinMaxHeight - 115, 0), Vector3(200, 40, 1), false);
	PlayerHPBar * playerHPBar = new PlayerHPBar(Vector3(250, WinMaxHeight - 115, 0), Vector3(200, 40, 1));
	playerHPBar->SetPlayer(player);
	Pannel * mpBar = new Pannel(TexturePath + L"UI/EnergyBarFill.png", Vector3(265, WinMaxHeight - 138, 0), Vector3(170, 20, 1), false);
	Pannel * BombSlot = new Pannel(TexturePath + L"UI/bomb_back.png", Vector3(265, WinMaxHeight - 170, 0), Vector3(40, 40, 1), false);
	Pannel * BombSlot2 = new Pannel(TexturePath + L"UI/bomb_back.png", Vector3(225, WinMaxHeight - 170, 0), Vector3(40, 40, 1), false);
	Pannel * BombSlot3 = new Pannel(TexturePath + L"UI/bomb_back.png", Vector3(305, WinMaxHeight - 170, 0), Vector3(40, 40, 1), false);
	//Pannel * Bomb = new Pannel(TexturePath + L"UI/bomb.png", Vector3(265, WinMaxHeight - 170, 0), Vector3(40, 40, 1), false);
	
	Pannel * headIcon = new Pannel(TexturePath + L"UI/headIcon.png", Vector3(100, WinMaxHeight - 123, 0), Vector3(100, 100, 1), false);

}

void TestStage::Destroy()
{

	//SAFE_DELETE(flock);
	player->Delete();
	crossHair->Delete();
	//SAFE_DELETE(player);
	//SAFE_DELETE(crossHair);
	SAFE_DELETE(mapGen);

	//GameObjectManager::Delete();
	GameObjectManager::Delete();
	RenderManager::Delete();
	RespawnManager::Delete();
	FlockManager::Delete();
	EventManager::Delete();
	Camera::Delete();
}

void TestStage::Update()
{
	Camera::Get()->Update();

	//flock->Update();
	//GameObjectManager::Get()->Update();
	if (GameObjectManager::Get())
	{
		RespawnManager::Get()->Update();
		FlockManager::Get()->Update();
		EventManager::Get()->Update();
		mapGen->Update();

		GameObjectManager::Get()->Update();
	}
}

void TestStage::PreRender()
{
	RenderManager::Get()->PreRender();
}

void TestStage::Render()
{
	Camera::Get()->Render();
	RenderManager::Get()->Render();
}

void TestStage::GUI()
{
}
