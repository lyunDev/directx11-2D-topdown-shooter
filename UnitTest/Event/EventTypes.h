#pragma once
#include "stdafx.h"

namespace BattleEvent
{
	static const string KillEnemy = "BattleEvent.KillEnemy";
	static const string KillBoss = "BattleEvent.KillBoss";
}

namespace SceneEvent
{
	static const string Transition = "SceneEvent.Transition";
}

namespace GameEvent
{
	static const string BossAppear = "GameEvent.BossAppear";
	static const string BossCaution = "GameEvent.BossCaution";
	static const string BossDie = "GameEvent.BossDie";
	static const string PlayerDie = "GameEvent.PlayerDie";
}
