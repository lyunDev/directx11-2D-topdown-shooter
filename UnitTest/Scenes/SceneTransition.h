#pragma once
#include "Interfaces/IObject.h"
class SceneTransition
{
public :
	SceneTransition();
	~SceneTransition();
	IObject * GetCurrentScene();

	void PushScene(string sceneName, IObject * scene, function<void(IObject *, IObject * )> onChanged);


	// 바뀔때 push하는거 콜백으로 받음
	
private :
	IObject * currentScene = nullptr;
	vector<IObject * > scenes;
};