#include "Framework.h"
#include "ColTestDemo.h"

#include "Geometries/Rect.h"


void ColTestDemo::Init()
{
	r1 = new Rect({ 100, 100, 0 }, { 100, 100, 1 }, 0.0f);
	r2 = new Rect({ 0, 0, 0 }, { WinMaxWidth, WinMaxHeight, 1 }, 0.0f);

	upStage = new Rect({ 0, WinMaxHeight, 0 }, { WinMaxWidth, 10, 1 }, 0.0f);
	leftStage = new Rect({ WinMaxWidth, 0, 0 }, { 10, WinMaxHeight, 1 }, 0.0f);
	rightStage = new Rect({ 0, 0, 0 }, { 10, WinMaxHeight, 1 }, 0.0f);
	downStage = new Rect({ 0, 0, 0 }, { WinMaxWidth, 10, 1 }, 0.0f);
	// LT -> 100, 200
	// RB -> 200, 100
}

void ColTestDemo::Destroy()
{
	SAFE_DELETE(r2);
	SAFE_DELETE(r1);
}

void ColTestDemo::Update()
{
	upStage->Update();
	leftStage->Update();
	rightStage->Update();
	downStage->Update();
	r1->Update();

	//r2->Update();
	//r1->Move();

	/*if (r1->GetBox()->IsOutOfBoxVertex(r2->GetBox()) == true)
		r2->SetColor(Values::Green);
	else
		r2->SetColor(Values::White);*/


	//if (r1->AABB(upStage->GetBox()) == true)
	//{
	//	direction = Direction::Down;
	//}
	//if (r1->AABB(leftStage->GetBox()) == true)
	//{
	//	direction = Direction::Right;
	//}
	//if (r1->AABB(downStage->GetBox()) == true)
	//{
	//	direction = Direction::Up;
	//}
	//if (r1->AABB(rightStage->GetBox()) == true)
	//{
	//	direction = Direction::Left;
	//}
	//switch (direction)
	//{
	//case Direction::Down :
	//	r1->SetPosition({r1->GetPosition().x, r1->GetPosition().y - 1, r1->GetPosition().z});
	//	break;
	//case Direction::Right :
	//	r1->SetPosition({ r1->GetPosition().x + 1, r1->GetPosition().y, r1->GetPosition().z });
	//	break;
	//case Direction::Left:
	//	r1->SetPosition({ r1->GetPosition().x - 1, r1->GetPosition().y, r1->GetPosition().z });
	//	break;
	//case Direction::Up:
	//	r1->SetPosition({ r1->GetPosition().x, r1->GetPosition().y + 1, r1->GetPosition().z });
	//	break;
	//}
}

void ColTestDemo::PreRender()
{
}

void ColTestDemo::Render()
{

	//r2->Render();
	r1->Render();
	upStage->Render();
	leftStage->Render();
	rightStage->Render();
	downStage->Render();
}

void ColTestDemo::GUI()
{
}
