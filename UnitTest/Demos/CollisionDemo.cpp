#include "Framework.h"
#include "CollisionDemo.h"

#include "Geometries/Rect.h"


void CollisionDemo::Init()
{
	r1 = new Rect({ 100, 100, 0 }, { 100, 100, 1 }, 0.0f);
	r2 = new Rect({ 300, 300, 0 }, { 100, 100, 1 }, 0.0f);
	// LT -> 100, 200
	// RB -> 200, 100

	switchPtrs.push_back(r1->GetBox()->GetFuncPtr());
	switchPtrs.push_back(r2->GetBox()->GetFuncPtr());
}

void CollisionDemo::Destroy()
{
	SAFE_DELETE(r2);
	SAFE_DELETE(r1);
}

void CollisionDemo::Update()
{
	r1->Update();
	r2->Update();
	r1->Move();
	if (BoundingBox::AABB(r1->GetBox(), r2->GetBox()) == true)
		r2->SetColor(Values::Green);
	else
		r2->SetColor(Values::Red);

}

void CollisionDemo::PreRender()
{
}

void CollisionDemo::Render()
{
	r1->Render();
	r2->Render();
}

void CollisionDemo::GUI()
{
	ImGui::Begin("CollisionSwitch");
	{
		if (ImGui::Button("Switch", ImVec2(100, 30)))
			for (function<void()> f : switchPtrs)
				f();
	}
	ImGui::End();
}
