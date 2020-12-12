#include "stdafx.h"
#include "Program.h"
#include "Systems/Window.h"


//#include "Demos/RectDemo.h"
#include "Demos/GUIDemo.h"
#include "Demos/TMapDemo.h"
//#include "Demos/FileStreamDemo.h"
//#include "Demos/JsonDemo.h"
#include "Scenes/TestStage.h"
#include "Scenes/MainScene.h"

#include "Scenes/SceneTransition.h"
#include "Event/EventTypes.h"
#include "Event/EventDispatcher.h"
void Program::Init()
{
	//Camera::Create();
	States::Create();

	sceneTransition = new SceneTransition();
	sceneTransition->PushScene("TestStage", new TestStage(), [&](IObject * beforeScene ,IObject * scene)
	{
		Pop(beforeScene);
		Push(scene);
	});
	sceneTransition->PushScene("MainScene", new MainScene(), [&](IObject * beforeScene, IObject * scene)
	{
		Pop(beforeScene);
		Push(scene);
	});
	/*sceneTransition->PushScene("EditScene", new EditScene(), [&](IObject * beforeScene, IObject * scene)
	{
		Pop(beforeScene);
		Push(scene);
	});*/
	EventDispatcher::TriggerEvent(SceneEvent::Transition + "MainScene");

	//Push(new GUIDemo());
	//Push(new TestStage());
}

void Program::Destroy()
{
	//Camera::Delete();
	//SAFE_DELETE(vpb);
	for (IObject* obj : objs)
	{
		obj->Destroy();
		SAFE_DELETE(obj);
	}
	Textures::Delete();
}

void Program::Update()
{
	//Camera::Get()->Update();
	for (IObject* obj : objs)
		obj->Update();
}

void Program::Render()
{
	//Camera::Get()->Render();
	//vpb->SetVSBuffer(1);
	for (IObject* obj : objs)
		obj->Render();
}

void Program::PreRender()
{
	//Camera::Get()->Render();
	for (IObject* obj : objs)
		obj->PreRender();
}

void Program::GUI()
{
	for (IObject* obj : objs)
		obj->GUI();
}

void Program::Push(IObject * obj)
{
	objs.push_back(obj);
	//obj->Init();
}

void Program::Pop(IObject * obj)
{
	for (int i = 0; i < objs.size(); i++)
	{
		if (objs[i] == obj)
			objs.erase(objs.begin() + i);
	}
}



int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevINSTANCE, LPSTR param, int command)
{
	//프로그램의 인스턴스 핸들 / 프로그램의 식별자 / 인스턴스는 객체 라고 생각하면됨.
	srand((UINT)time(NULL));

	DXDesc desc;
	desc.AppName = L"D2DGame";
	desc.instance = instance;
	desc.handle = NULL;
	desc.width = WinMaxWidth;
	desc.height = WinMaxHeight;

	Program* program = new Program();
	Window* window = new Window(desc);

	WPARAM wParam = window->Run(program);
	SAFE_DELETE(window);
	SAFE_DELETE(program);

	return wParam;
}