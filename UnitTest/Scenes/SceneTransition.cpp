#include "stdafx.h"
#include "SceneTransition.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"

SceneTransition::SceneTransition()
{
}

SceneTransition::~SceneTransition()
{
	for (auto scene : scenes)
	{
		SAFE_DELETE(scene);
	}
	scenes.clear();
}

IObject * SceneTransition::GetCurrentScene()
{
	return this->currentScene;
}

void SceneTransition::PushScene(string sceneName, IObject * scene, function<void(IObject*, IObject*)> onChanged)
{
	
	EventDispatcher::AddEventListener(SceneEvent::Transition + sceneName, [=]() 
	{
		if(currentScene != nullptr)
			currentScene->Destroy();
		scene->Init();
		onChanged(currentScene, scene);
		currentScene = scene;
		
	});
}

