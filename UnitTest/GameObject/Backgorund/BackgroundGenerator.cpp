#include "stdafx.h"
#include "BackgroundGenerator.h"
#include "Game/GameObjectManager.h"
BackgroundGenerator::BackgroundGenerator()
{
}

BackgroundGenerator::~BackgroundGenerator()
{
	for (auto bg : backgrounds)
	{
		SAFE_DELETE(bg);
	}
	backgrounds.clear();
}

void BackgroundGenerator::Update()
{
	CullBackground();
	auto center = GetBgUnderPlayer();
	assert(center != nullptr);
	GenerateType genType = CheckGenerateCondition(center);
	if (genType == NONE) return;
	// 현재 쉬고있는 bg 하나를 받아온다.
	Background * restingBg = (cpplinq::from_iterators(backgrounds.begin(), backgrounds.end())
		>> cpplinq::where([](Background * bg) {return !bg->GetActive(); })
		>> cpplinq::to_vector()).back();
	assert(restingBg != nullptr);

	switch (genType)
	{
	case BG::LEFT:
		restingBg->transform->position.x = center->transform->position.x - center->transform->size.x;
		restingBg->transform->position.y = center->transform->position.y;
		break;
	case BG::LEFT_TOP:
		restingBg->transform->position.x = center->transform->position.x - center->transform->size.x;
		restingBg->transform->position.y = center->transform->position.y + center->transform->size.y;
		break;
	case BG::LEFT_BOTTOM:
		restingBg->transform->position.x = center->transform->position.x - center->transform->size.x;
		restingBg->transform->position.y = center->transform->position.y - center->transform->size.y;
		break;
	case BG::RIGHT:
		restingBg->transform->position.x = center->transform->position.x + center->transform->size.x;
		restingBg->transform->position.y = center->transform->position.y;
		break;
	case BG::RIGHT_TOP:
		restingBg->transform->position.x = center->transform->position.x + center->transform->size.x;
		restingBg->transform->position.y = center->transform->position.y + center->transform->size.y;
		break;
	case BG::RIGHT_BOTTOM:
		restingBg->transform->position.x = center->transform->position.x + center->transform->size.x;
		restingBg->transform->position.y = center->transform->position.y - center->transform->size.y;
		break;
	case BG::TOP:
		restingBg->transform->position.x = center->transform->position.x;
		restingBg->transform->position.y = center->transform->position.y + center->transform->size.y;
		break;
	case BG::BOTTOM:
		restingBg->transform->position.x = center->transform->position.x;
		restingBg->transform->position.y = center->transform->position.y - center->transform->size.y;
		break;
	default:
		break;
	}
	restingBg->SetActive(true);
}

void BackgroundGenerator::CullBackground()
{
	//auto player = GameObjectManager::Get()->FindObjectsWithTag("Player").back();
	Vector3 cameraPos = Camera::Get()->GetPos();
	cameraPos.x += WinMaxWidth * 0.5f;
	cameraPos.y += WinMaxHeight * 0.5f;
	
	auto bgs = cpplinq::from_iterators(backgrounds.begin(), backgrounds.end())
		>> cpplinq::where([](Background * bgPtr) {return bgPtr->GetActive(); })
		>> cpplinq::to_vector();
	for (auto bg : bgs)
	{
		float distX = std::abs(cameraPos.x - bg->transform->position.x);
		float distY = std::abs(cameraPos.y - bg->transform->position.y);

		if (distX > bg->transform->size.x || distY > bg->transform->size.y)
			bg->SetActive(false);
	}
	return;
}

Background * BackgroundGenerator::GetBgUnderPlayer()
{
	//auto player = GameObjectManager::Get()->FindObjectsWithTag("Player").back();
	//auto player = GameObjectManager::Get()->FindObjectsWithTag("Player").back();
	Vector3 cameraPos = Camera::Get()->GetPos();
	cameraPos.x += WinMaxWidth * 0.5f;
	cameraPos.y += WinMaxHeight * 0.5f;
	auto bgs = cpplinq::from_iterators(backgrounds.begin(), backgrounds.end())
		>> cpplinq::where([](Background * bgPtr) {return bgPtr->GetActive(); })
		>> cpplinq::to_vector();
	for (auto bg : bgs)
	{
		if (bg->GetActive() == false) continue;

		Vector3 leftTop = Vector3
		(
			bg->transform->position.x - bg->transform->size.x * 0.5f,
			bg->transform->position.y + bg->transform->size.y * 0.5f,
			0
		);
		Vector3 rightBottom = Vector3
		(
			bg->transform->position.x + bg->transform->size.x * 0.5f,
			bg->transform->position.y - bg->transform->size.y * 0.5f,
			0
		);
		if (leftTop.x < cameraPos.x
			&& leftTop.y > cameraPos.y
			&& rightBottom.x > cameraPos.x
			&& rightBottom.y < cameraPos.y)
		{
			return bg;
		}
	}
	// 말 안됨
	//assert(false);
	return nullptr;
}

GenerateType BackgroundGenerator::CheckGenerateCondition(Background * center)
{
	//auto player = GameObjectManager::Get()->FindObjectsWithTag("Player").back();
	//auto player = GameObjectManager::Get()->FindObjectsWithTag("Player").back();
	Vector3 cameraPos = Camera::Get()->GetPos();
	cameraPos.x += WinMaxWidth * 0.5f;
	cameraPos.y += WinMaxHeight * 0.5f;
	Vector3 playerLeftTop = Vector3
	(
		cameraPos.x - center->transform->size.x * 0.5f,
		cameraPos.y + center->transform->size.y * 0.5f,
		0
	);
	Vector3 playerRightBottom = Vector3
	(
		cameraPos.x + center->transform->size.x * 0.5f,
		cameraPos.y - center->transform->size.y * 0.5f,
		0
	);
	Vector3 centerLeftTop = Vector3
	(
		center->transform->position.x - center->transform->size.x * 0.5f,
		center->transform->position.y + center->transform->size.y * 0.5f,
		0
	);
	Vector3 centerRightBottom = Vector3
	(
		center->transform->position.x + center->transform->size.x * 0.5f,
		center->transform->position.y - center->transform->size.y * 0.5f,
		0
	);

	bool left = false;
	bool right = false;
	bool bottom = false;
	bool top = false;
	// 왼쪽 넘어갔는지 확인
	if (playerLeftTop.x < centerLeftTop.x)
		left = true;
	// 위쪽 넘어갔는지 확인
	if (playerLeftTop.y > centerLeftTop.y)
		top = true;
	// 아래쪽 넘어갔는지 확인
	if (playerRightBottom.y < centerRightBottom.y)
		bottom = true;
	// 오른쪽 넘어갔는지 확인
	if (playerRightBottom.x > centerRightBottom.x)
		right = true;

	if (left)
	{
		// left
		Vector3 pos = Vector3
		(
			center->transform->position.x - center->transform->size.x,
			center->transform->position.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return LEFT;
	}
	if (left && top)
	{
		// left top
		Vector3 pos = Vector3
		(
			center->transform->position.x - center->transform->size.x,
			center->transform->position.y + center->transform->size.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return LEFT_TOP;
	}
	if (left && bottom)
	{
		// left bottom
		Vector3 pos = Vector3
		(
			center->transform->position.x - center->transform->size.x,
			center->transform->position.y - center->transform->size.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return LEFT_BOTTOM;
	}
	if (right)
	{
		// right
		Vector3 pos = Vector3
		(
			center->transform->position.x + center->transform->size.x,
			center->transform->position.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return RIGHT;
	}
	if (right && top)
	{
		// right top
		Vector3 pos = Vector3
		(
			center->transform->position.x + center->transform->size.x,
			center->transform->position.y + center->transform->size.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return RIGHT_TOP;
	}
	if (right && bottom)
	{
		// right bottom
		Vector3 pos = Vector3
		(
			center->transform->position.x + center->transform->size.x,
			center->transform->position.y - center->transform->size.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return RIGHT_BOTTOM;
	}
	if (top)
	{
		// top
		Vector3 pos = Vector3
		(
			center->transform->position.x,
			center->transform->position.y + center->transform->size.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return TOP;
	}
	if (bottom)
	{
		// bottom
		Vector3 pos = Vector3
		(
			center->transform->position.x,
			center->transform->position.y - center->transform->size.y,
			0
		);
		if (!IsExistsAtPos(pos))
			return BOTTOM;
	}

	return NONE;
}

bool BackgroundGenerator::IsExistsAtPos(Vector3 pos)
{
	auto bgs = cpplinq::from_iterators(backgrounds.begin(), backgrounds.end())
		>> cpplinq::where([](Background * bgPtr) {return bgPtr->GetActive(); })
		>> cpplinq::to_vector();
	for (auto bg : bgs)
	{
		if (bg->GetActive() == true && bg->transform->position == pos)
			return true;
	}
	return false;
}
