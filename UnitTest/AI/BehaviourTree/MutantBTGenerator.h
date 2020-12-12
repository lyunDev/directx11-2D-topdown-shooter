#pragma once
#include "Utilities/BrainTree.h"
#include "MutantNodes.h"
class MutantBTGenerator 
{
public :
	static BrainTree::BehaviorTree GenerateBehaviourTreeManually(GameObject * owner)
	{
		BrainTree::BehaviorTree tree;
		auto selector = std::make_shared<BrainTree::Selector>();
		auto isInOfRange = std::make_shared<IsInOfChaseRange>(owner);
		auto sequence2 = std::make_shared<BrainTree::Sequence>();
		auto isActiveShield = std::make_shared<IsActiveShield>();
		auto isExplosionState = std::make_shared<IsExplosionState>();
		auto movingAction = std::make_shared<MovingAction>(owner);
		auto activeShield = std::make_shared<ShieldAction>(owner);
		auto explosionAction = std::make_shared<ExplosionAction>(owner);
		auto selector2 = std::make_shared<BrainTree::Selector>();
		auto isActivePatternOne = std::make_shared<IsActivePatternOne>();
		auto isActivePatternTwo = std::make_shared<IsActivePatternTwo>();
		auto isActivePatternThree = std::make_shared<IsActivePatternThree>();
		auto sequence3 = std::make_shared<BrainTree::Sequence>();
		auto sequence4 = std::make_shared<BrainTree::Sequence>();
		auto selector3 = std::make_shared<BrainTree::Selector>();
		auto sequence5 = std::make_shared <BrainTree::Sequence>();
		auto sequence6 = std::make_shared<BrainTree::Sequence>();
		auto sequence7 = std::make_shared<BrainTree::Sequence>();
		auto activeShield2 = std::make_shared<ShieldAction>(owner);
		auto movingAction2 = std::make_shared<MovingAction>(owner);
		auto movingAction3 = std::make_shared<MovingAction>(owner);
		auto normalShootAction = std::make_shared<NormalShootAction>(owner);
		auto normalShootAction2 = std::make_shared<NormalShootAction>(owner);
		auto normalShootAction3 = std::make_shared<NormalShootAction>(owner);

		tree.setRoot(selector);
		selector->addChild(isInOfRange);
		selector->addChild(sequence5);
		isInOfRange->setChild(selector2);
		selector2->addChild(isActivePatternOne);
		selector2->addChild(isActivePatternTwo);
		selector2->addChild(isActivePatternThree);
		isActivePatternOne->setChild(sequence2);
		sequence2->addChild(normalShootAction);
		//TODO : 여기서 첫번째 패턴 더 추가하기 (sequence2)
		isActivePatternTwo->setChild(sequence3);
		sequence3->addChild(normalShootAction2);
		//TODO : 여기서 두번째 패턴 더 추가하기 (sequence3)
		isActivePatternThree->setChild(sequence4);
		sequence4->addChild(normalShootAction3);
		sequence4->addChild(activeShield);
		//TODO : 여기서 세번째 패턴 더 추가하기 (sequence4)
		
		sequence5->addChild(selector3);
		sequence5->addChild(movingAction);
		selector3->addChild(isActiveShield);
		selector3->addChild(isExplosionState);
		isActiveShield->setChild(sequence6);
		sequence6->addChild(activeShield2);
		sequence6->addChild(movingAction2);
		isExplosionState->setChild(sequence7);
		sequence7->addChild(movingAction3);
		sequence7->addChild(explosionAction);

		return tree;
	}

};