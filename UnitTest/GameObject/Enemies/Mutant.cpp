#include "stdafx.h"
#include "Mutant.h"
#include "AI/FSM/EnemyState.h"
#include "GameObject/HPBar.h"
Mutant::Mutant()
	: EnemyUnit(ActorInfo(600, 120), Vector3(130, 150, 1))
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Mutant.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetRenderToCollisionBox(true);

	//enemyState = new EnemyAI::ThinkingState();
	behaviourTree = MutantBTGenerator::GenerateBehaviourTreeManually(this);
	bShootable = false;
	hpBar = new HPBar(this, &actorInfo, false);
	hpBar->SetActive(false);
	SetTag("Boss");
}

Vector3 Mutant::GetFirePosOffset()
{
	return Vector3(-15, 120, 0);
}

void Mutant::OnUpdate()
{
	EnemyUnit::OnUpdate();
	behaviourTree.update();
	if (actorInfo.isDie && isDieEventTrigger == false)
	{
		hpBar->SetActive(false);
		isDieEventTrigger = true;
		EventDispatcher::TriggerEvent(BattleEvent::KillBoss);
	}
}

void Mutant::OnRespawn(Vector3 reapawnPos, float respawnRot)
{
	EnemyUnit::OnRespawn(reapawnPos, respawnRot);
	hpBar->SetActive(true);
}
