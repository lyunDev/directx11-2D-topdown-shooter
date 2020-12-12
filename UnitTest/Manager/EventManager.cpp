#include "stdafx.h"
#include "EventManager.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"
#include "GameUI/BossCautionPannel.h"
#include "GameUI/BossHPBar.h"
#include "MySQL/LogManager.h"
#include "GameUI/GameClearPannel.h"
#include "GameUI/FadeInOut.h"
void EventManager::Update()
{
	currentTime += Time::Delta();
	// 보스 등장 시간 - 5초
	if (currentTime > 150 && bBossCaution == false)
	{
		bBossCaution = true;
		EventDispatcher::TriggerEvent(GameEvent::BossCaution);
	}
}

void EventManager::BossCaution(void)
{
	// warning ui를 띄운다.
	// test
	BossCautionPannel * pannel = new BossCautionPannel();
	pannel->Caution();
	Log log(1, "Boss appear");
	LogManager::Get()->InsertLog(log);
	//BossHPBar * bossHPBar = new BossHPBar();
}

void EventManager::KillBoss()
{
	// todo : 이거 게임 오버로 변경
	/*BossCautionPannel * pannel = new BossCautionPannel();
	pannel->Caution();*/
	GameClearPannel * pannel = new GameClearPannel();
	pannel->Clear([]() 
	{
		EventDispatcher::TriggerEvent(SceneEvent::Transition + "MainScene");
	});
	
	Log log(1, "kill boss");
	LogManager::Get()->InsertLog(log);
}

void EventManager::KillEnemy()
{
	Log log(1, "Test_killEnemy");
	LogManager::Get()->InsertLog(log);
}

void EventManager::DiePlayer()
{
	FadeInOut * fadeInOut = new FadeInOut();
	fadeInOut->FadeOut([]() 
	{
		EventDispatcher::TriggerEvent(SceneEvent::Transition + "MainScene");
	});
}


EventManager::EventManager()
{
	EventDispatcher::AddEventListener(GameEvent::BossCaution, std::bind(&EventManager::BossCaution, this));
	EventDispatcher::AddEventListener(BattleEvent::KillBoss, std::bind(&EventManager::KillBoss, this));
	EventDispatcher::AddEventListener(BattleEvent::KillEnemy, std::bind(&EventManager::KillEnemy, this));
	EventDispatcher::AddEventListener(GameEvent::PlayerDie, std::bind(&EventManager::DiePlayer, this));
}

EventManager::~EventManager()
{
}
