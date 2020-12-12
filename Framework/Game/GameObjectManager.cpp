#include "Framework.h"
#include "GameObjectManager.h"
#include "Utilities/CollisionBox.h"
#include "GameObject.h"
#include "Game/Transform.h"

void GameObjectManager::PushGameObject(GameObject* gameObject)
{
	
	gameObjects.push_back(gameObject);
	//if (gameObject->GetObjectLayer() != ObjectLayer::EFFECT)
	//	collisions.push_back(gameObject);
	//SortObject();
}

void GameObjectManager::PopGameObject(GameObject* gameObject)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i] == gameObject)
		{
			gameObjects.erase(gameObjects.begin() + i);
		}
	}
}

void GameObjectManager::DeleteGameObject(GameObject * gameObject)
{
	deletedObjects.push(gameObject);
}

void GameObjectManager::Update()
{
	SortObject();
	CheckCollision();
	auto activeObjs = cpplinq::from_iterators(gameObjects.begin(), gameObjects.end())
		>> cpplinq::where([&](GameObject* objPtr) 
	{
		if (objPtr->GetActive() == false)
			return false;
		auto player = GetPlayer();
		if (player)
		{
			float dist = DxMath::GetDist(player->transform->position, objPtr->transform->position);
			if (dist > WinMaxWidth && objPtr->GetObjectLayer() != ObjectLayer::BACKGROUND && 
				objPtr->GetObjectLayer() != ObjectLayer::UI &&
				objPtr->GetTag() != "Boss")
				return false;
		}
		return true;
	})
		>> cpplinq::to_vector();
	
	/*for (auto go : activeObjs)
	{
		go->Update();
	}*/
	//for (int i = 0; i < activeObjs.size(); i++)
	//{
	//	activeObjs[i]->Update();
	//}

	for (auto activeObj : activeObjs)
	{
		if (isDeleted)return;
		if (gameObjects.size() == 0)return;
		activeObj->Update();
	}

	while (deletedObjects.size() != 0 && !isDeleted)
	{
		auto deletedObj = deletedObjects.front();
		SAFE_DELETE(deletedObj);
		deletedObjects.pop();
	}
	//for (int i = 0; i < gameObjects.size(); i++)
	//{
	//	if (gameObjects[i]->GetActive() == false)
	//		continue;
	//	gameObjects[i]->Update();
	//}

	/*if (reservedDeletion)
		GameObjectManager::Delete();*/

}

void GameObjectManager::DeferredDelete()
{
	isDeleted = true;
}

void GameObjectManager::SortObject()
{
	sort(gameObjects.begin(), gameObjects.end(), [](GameObject* lhs, GameObject* rhs)->bool
	{
		if (lhs->GetObjectLayer() >= rhs->GetObjectLayer())
			return false;
		else
			return true;
	});
}

void GameObjectManager::LayerChanged()
{
	SortObject();

}

vector<GameObject*> GameObjectManager::FindObjectsWithTag(string tag)
{
	vector<GameObject*> ret;
	for (auto go : gameObjects)
	{
		if (go->GetTag() == tag)
			ret.push_back(go);
	}
	return ret;
}

vector<GameObject*> GameObjectManager::FindObjectsWithDistance(GameObject *  owner, float distance, ObjectLayer objLayer)
{
	auto culledObjs = cpplinq::from_iterators(gameObjects.begin(), gameObjects.end())
		>> cpplinq::where([&](GameObject * objPtr)
	{
		if (objPtr->GetActive() == false)
			return false;

		if (objLayer != ObjectLayer::DEFAULT && objPtr->GetObjectLayer() != objLayer)
			return false;
		if (objPtr == owner)
			return false;
		float dist = DxMath::GetDist(owner->transform->position, objPtr->transform->position);
		if (dist > distance)
			return false;
		return true;
	}) >> cpplinq::to_vector();
			
	return culledObjs;
}

GameObject * GameObjectManager::GetPlayer()
{
	if (player == nullptr)
	{
		for (auto go : gameObjects)
		{
			if (go->GetObjectLayer() == ObjectLayer::PLAYER)
			{
				player = go;
				break;
			}
		}
	}
	return player;
}


GameObjectManager::GameObjectManager()
{
	isDeleted = false;
}

GameObjectManager::~GameObjectManager()
{
	isDeleted = true;
	gameObjects.clear();
	while (deletedObjects.size() != 0)
	{
		auto deleteObj = deletedObjects.front();
		SAFE_DELETE(deleteObj);
		deletedObjects.pop();
	}

	player = nullptr;
}

void GameObjectManager::CheckCollision()
{
	auto preOtherObjs = cpplinq::from_iterators(gameObjects.begin(), gameObjects.end())
		>> cpplinq::where([&](GameObject * objPtr)
	{
		if (objPtr->GetActive() == false)
			return false;
		if (objPtr->GetObjectLayer() == ObjectLayer::BACKGROUND)
			return false;
		if (objPtr->GetObjectLayer() == ObjectLayer::EFFECT)
			return false;
		if (objPtr->GetObjectLayer() == ObjectLayer::UI)
			return false;
		// 화면 밖일 경우 업데이트 목록에서 제외한다.
		auto player = GetPlayer();
		if (player)
		{
			float dist = DxMath::GetDist(player->transform->position, objPtr->transform->position);
			if (dist > WinMaxWidth)
				return false;
		}
		return true;
	}) >> cpplinq::to_vector();

	// collision check
	auto colObjs = cpplinq::from_iterators(preOtherObjs.begin(), preOtherObjs.end())
		>> cpplinq::where([&](GameObject * objPtr) 
	{
		if (objPtr->GetActive() == false)
			return false;
		if (objPtr->IsRigidbody() == false)
			return false;
	
		return true;
	}) >> cpplinq::to_vector();

	
	for (auto go : colObjs)
	{

		// 조건에 해당 안되는 오브젝트들은 미리 제거한다.
		auto otherObjs = cpplinq::from_iterators(preOtherObjs.begin(), preOtherObjs.end())
			>> cpplinq::where([&](GameObject * objPtr)
		{
			if (go == objPtr)
				return false;
			if (objPtr->GetObjectLayer() == ObjectLayer::EFFECT)
				return false;
			if (objPtr->GetObjectLayer() == ObjectLayer::BACKGROUND)
				return false;
			if (objPtr->GetActive() == false)
				return false;
			// 플레이어 계열끼리는 충돌체크 필요없음
			if ((go->GetObjectLayer() == ObjectLayer::PLAYER || go->GetObjectLayer() == ObjectLayer::PLAYER_BULLET)
				&& (objPtr->GetObjectLayer() == ObjectLayer::PLAYER || objPtr->GetObjectLayer() == ObjectLayer::PLAYER_BULLET))
				return false;
			// 에너미 계열끼리는 충돌체크 필요없음
			if ((go->GetObjectLayer() == ObjectLayer::ENEMY || go->GetObjectLayer() == ObjectLayer::ENEMY_BULLET)
				&& (objPtr->GetObjectLayer() == ObjectLayer::ENEMY || objPtr->GetObjectLayer() == ObjectLayer::ENEMY_BULLET))
				return false;
			// 총알 끼리는 충돌체크 필요없음
			if ((go->GetObjectLayer() == ObjectLayer::ENEMY_BULLET || go->GetObjectLayer() == ObjectLayer::PLAYER_BULLET)
				&& (objPtr->GetObjectLayer() == ObjectLayer::ENEMY_BULLET || objPtr->GetObjectLayer() == ObjectLayer::PLAYER_BULLET))
				return false;
			// 플레이어와 일정 거리 떨어져있으면(화면 밖이면) 업데이트 안함
			auto player = GetPlayer();
			if (player)
			{
				float dist = DxMath::GetDist(player->transform->position, objPtr->transform->position);
				if (dist > WinMaxWidth)
					return false;
				float distance = DxMath::GetDist(go->transform->position, objPtr->transform->position);
				float scaleSum = (max(go->transform->size.x, go->transform->size.y) *0.5f) + (max(objPtr->transform->size.x, objPtr->transform->size.y) * 0.5f);
				if (distance > scaleSum)
					return false;
			}
			return true;
		}) >> cpplinq::to_vector();

		for (auto other : otherObjs)
		{


			//TODO : 이벤트 방식 
			// 

			// collision 연산 중 active 변경될 수 있음
			if (go->GetActive() == false)
				break;
			bool isStaying = go->GetCollisionBox()->IsStaying(other->GetCollisionBox());
			if (go->GetCollisionBox()->OBB(other->GetCollisionBox()))
			{
				// 만약 colliisonStayList에 있으면 OnCollisionStay호출
				// 없으면 OnCollisionEnter호출하고 StayList에 넣음
				if (isStaying)
				{
					go->OnCollisionStay(other);
				}
				else
				{
					go->OnCollisionEnter(other);
					go->GetCollisionBox()->PushStayedCollider(other->GetCollisionBox());
				}
			}
			else
			{
				// 만약 CollisionStayList에 있으면 OnCollisionExit 호출하고 StayList에서 제외
				if (isStaying)
				{
					go->OnCollisionExit(other);
					go->GetCollisionBox()->PopStayedCollider(other->GetCollisionBox());
				}
			}
		}
	}
}


