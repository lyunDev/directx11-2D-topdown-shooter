#pragma once
#include "EnemyUnit.h"
#include "GameObject/Projectiles/IonBlueBullet.h"
#include "GameObject/Projectiles/IonBlueMuzzleFlash.h"
#include "Utilities/BrainTree.h"
#include "AI/BehaviourTree/MutantNodes.h"
#include "AI/BehaviourTree/MutantBTGenerator.h"

class Mutant : public EnemyUnit<IonBlueBullet, IonBlueMuzzleFlash>
{
public :
	Mutant();

	virtual Vector3 GetFirePosOffset() override;
	virtual void OnUpdate() override;
	virtual void OnRespawn(Vector3 reapawnPos, float respawnRot) override;

private :
	BrainTree::BehaviorTree behaviourTree;
	class HPBar * hpBar;

	bool isDieEventTrigger = false;
};