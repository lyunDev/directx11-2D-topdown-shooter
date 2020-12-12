#include "stdafx.h"
#include "RectDemo.h"
#include "Geometries/Rect.h"
void RectDemo::Init()
{
	for (Rect* r : rects)
		r = new Rect(Vector3(620, 360, 0), Vector3(100, 100, 1), 0.0f);
}

void RectDemo::Destroy()
{
	for (Rect* r : rects)
		SAFE_DELETE(r);
}

void RectDemo::Update()
{
	if (Mouse::Get()->Down(0))
		rects.push_back(new Rect(Mouse::Get()->GetPosition(), Vector3(100, 100, 1), 0.0f));
	for (Rect* r : rects)
		r->Update();
}

void RectDemo::Render()
{
	for (Rect* r : rects)
		r->Render();
}

void RectDemo::PreRender()
{

}

void RectDemo::GUI()
{
	ImGui::Begin("Rects");
	for (Rect* r : rects)
		r->GUI();
	ImGui::End();
}
