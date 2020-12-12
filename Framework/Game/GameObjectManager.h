#pragma once
#include "Utilities/Layers.h"
#include <queue>
class GameObject;
class GameObjectManager :public SingletonBase<GameObjectManager>
{
public :
	friend class SingletonBase<GameObjectManager>;

	void PushGameObject(GameObject* gameObject);
	void PopGameObject(GameObject* gameObject);
	void DeleteGameObject(GameObject* gameObject);

	
	void Update();
	void DeferredDelete();
	void LayerChanged();
	vector<GameObject*> FindObjectsWithTag(string tag);
	vector<GameObject*> FindObjectsWithDistance(GameObject*  obj, float distance, ObjectLayer objLayer = ObjectLayer::DEFAULT);
	GameObject * GetPlayer();
private :
	GameObjectManager();
	~GameObjectManager();

	void SortObject();
private :
	void CheckCollision();
private :
	vector<GameObject*> gameObjects;
	queue<GameObject*> deletedObjects;
	//vector<GameObject*> collisions;
	GameObject * player = nullptr;
	bool isDeleted = false;
};
