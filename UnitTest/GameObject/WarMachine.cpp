#include "stdafx.h"
#include "WarMachine.h"
#include "WarWeapon.h"
#include "Game/Transform.h"
#include "Effects/Dissolve.h"
#include "ShaderBuffers/ColorBuffer.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"
#include "Game/GameObjectManager.h"
//
//WarMachine::WarMachine(Vector3 position, Vector3 size, WarMachineType warMachineType, WarWeaponType warWeaponType)
//	: Actor(ActorInfo(100, 100), position, size, 0, false)
//{
//	Texture2D * tex = nullptr;
//	switch (warMachineType)
//	{
//	case WarMachineType::Heavy_1 :
//		break;
//	case WarMachineType::Heavy_2 :
//		break;
//	case WarMachineType::Heavy_3 :
//		break;
//	case WarMachineType::Light_1 :
//		break;
//	case WarMachineType::Light_2 :
//		break;
//	case WarMachineType::Light_3 :
//		break;
//	case WarMachineType::Light_4 :
//		 tex = new Texture2D(TexturePath + L"GameObject/WarMachines/Light4.png");
//		break;
//	case WarMachineType::Light_5 :
//		break;
//	}
//	SetSRV(tex->GetSRV());
//	SAFE_DELETE(tex);
//	SetRenderToCollisionBox(true);
//
//	switch (warWeaponType)
//	{
//	case WarWeaponType::Gun1_1:
//		break;
//	case WarWeaponType::Gun1_2:
//		break;
//	case WarWeaponType::Gun1_3:
//		break;
//	case WarWeaponType::Gun1_4:
//		break;
//	case WarWeaponType::Gun2:
//		break;
//	case WarWeaponType::Gun3_1:
//		break;
//	case WarWeaponType::Gun3_2:
//		//warWeapon = new WarWeapon(Vector3(transform->position.x, transform->position.y, 0), Vector3(100, 400, 1), warWeaponType);
//		warWeapon = make_shared<WarWeapon>(Vector3(transform->position.x, transform->position.y, 0), Vector3(100, 400, 1), warWeaponType);
//		break;
//	}
//
//	SetTag("Enemy");
//
//
//	// about shader 
//	Texture2D * map = new Texture2D(TexturePath + L"dissolveMap.jpg");
//	dissolveMap = map->GetSRV();
//	SAFE_DELETE(map);
//	
//	dissolveBuffer = new DissolveBuffer();
//	colorBuffer = new ColorBuffer();
//
//	SetActive(false);
//
//}

WarMachine::WarMachine()
	: Actor(ActorInfo(100, 100),Vector3(0, 0, 0), Vector3(500, 700, 1), 0, false)
{
	Texture2D * tex = nullptr;
	warMachineType = WarMachineType::Light_4;
	warWeaponType = WarWeaponType::Gun3_2;


	switch (warMachineType)
	{
	case WarMachineType::Heavy_1:
		break;
	case WarMachineType::Heavy_2:
		break;
	case WarMachineType::Heavy_3:
		break;
	case WarMachineType::Light_1:
		break;
	case WarMachineType::Light_2:
		break;
	case WarMachineType::Light_3:
		break;
	case WarMachineType::Light_4:
		tex = new Texture2D(TexturePath + L"GameObject/WarMachines/Light4.png");
		break;
	case WarMachineType::Light_5:
		break;
	}
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetRenderToCollisionBox(true);

	switch (warWeaponType)
	{
	case WarWeaponType::Gun1_1:
		break;
	case WarWeaponType::Gun1_2:
		break;
	case WarWeaponType::Gun1_3:
		break;
	case WarWeaponType::Gun1_4:
		break;
	case WarWeaponType::Gun2:
		break;
	case WarWeaponType::Gun3_1:
		break;
	case WarWeaponType::Gun3_2:
		//warWeapon = new WarWeapon(Vector3(transform->position.x, transform->position.y, 0), Vector3(100, 400, 1), warWeaponType);
		warWeapon = make_shared<WarWeapon>(Vector3(transform->position.x, transform->position.y, 0), Vector3(100, 400, 1), warWeaponType);
		warWeapon->SetActive(false);
		break;
	}

	SetTag("Enemy");


	// about shader 
	/*Texture2D * map = new Texture2D(TexturePath + L"dissolveMap.jpg");
	dissolveMap = map->GetSRV();
	SAFE_DELETE(map);

	dissolveBuffer = new DissolveBuffer();
	colorBuffer = new ColorBuffer();*/


	bulletPool = new ObjectPool<BlueSwirl>();
	firePoses.assign(36, Transform());
	for (int i = 0; i < 200; i++)
	{
		auto bullet = bulletPool->AccquireObject();
		activeBullets.push_back(bullet);
	}
	for (auto bullet : activeBullets)
	{
		bulletPool->ReleaseObject(bullet);
	}
	activeBullets.clear();

	SetActive(false);
	SetObjectLayer(ObjectLayer::ENEMY);
	SetRenderLayer(RenderLayer::ENEMY);
}

WarMachine::~WarMachine()
{
	//SAFE_DELETE(dissolveBuffer);

}

void WarMachine::OnCollisionEnter(GameObject * other)
{
	if (warWeapon->GetActive() == true)
		return;
	GameObject::OnCollisionEnter(other);
	
	if (other->GetObjectLayer() == ObjectLayer::PLAYER_BULLET)
	{
		Bullet * bullet = static_cast<Bullet *>(other);
		if (bullet == nullptr) return;
		Hit(bullet->GetBulletInfo().damage);
	}
}

void WarMachine::OnUpdate()
{
	Fire();
	BulletUpdate();

	// 일정거리 이상 떨어지면 false
	auto playerPos = GameObjectManager::Get()->GetPlayer()->transform->position;
	if (DxMath::GetDist(playerPos, transform->position) >= WinMaxWidth / 2 + 350)
	{
		warWeapon->SetActive(false);
		SetActive(false);
	}
	if (actorInfo.isDie == true)
	{
		GetDissolveBuffer()->IncreaseDissolveAmount(1 * Time::Delta());
		if (GetDissolveBuffer()->GetDissolveAmount() >= 1)
		{
			SetActive(false);
			EventDispatcher::TriggerEvent(BattleEvent::KillEnemy);
		}
	}
}

void WarMachine::OnRender()
{
	/*if (actorInfo.isDie)
	{
		SetShader(ShaderPath + L"Dissolve.hlsl");
		DC->PSSetShaderResources(1, 1, &dissolveMap);
		dissolveBuffer->SetPSBuffer(2);
	}
	else
	{
		SetShader(ShaderPath + L"TextureWithColor.hlsl");
		colorBuffer->SetPSBuffer(2);
	}*/
}

void WarMachine::OnPostRender()
{
	if (GetColorBuffer()->GetColor() == Color(1, 1, 1, 0))
		GetColorBuffer()->SetColor(Color(0, 0, 0, 0));
}

void WarMachine::OnRespawn(Vector3 respawnPos, float respawnRot)
{
	Actor::OnRespawn(respawnPos, respawnRot);
	GetDissolveBuffer()->SetDissolveAmount(0);
	transform->position = respawnPos;
	transform->rotation = respawnRot; 
	SetActive(true);

	warWeapon->OnRespawn(Vector3(respawnPos.x,respawnPos.y, 0), 0);
	warWeapon->SetActive(true);

}

void WarMachine::Hit(float damage)
{
	GetColorBuffer()->SetColor(Color(1, 1, 1, 0));
	actorInfo.Hit(damage);
}

void WarMachine::Fire()
{
	if (warWeapon->GetActive() == true)return;
	currentShootDelay += Time::Delta();
	if (currentShootDelay >= shootDelay)
	{
		currentShootDelay = 0;

		// 10단위였으면 5로 변경
		// 5 단위였으면 0으로 
		if (rotOffset % 10 == 0)
			rotOffset = 5;
		else
			rotOffset = 0;
		for (int i = 0; i < 36; i++)
		{
			if (activeBullets.size() >= bulletMaximum)
				return;
			rotOffset += i * 10;
			auto bullet = bulletPool->AccquireObject();
			activeBullets.push_back(bullet);

			firePoses[i].position = Vector3(0, 10, 0);
			firePoses[i].size = transform->size;
			firePoses[i].Rotate((float)D3DXToRadian(rotOffset));
			firePoses[i].position += transform->position;
			firePoses[i].rotation = rotOffset ;
			bullet->Fire(&firePoses[i]);
		}
	}
}

void WarMachine::BulletUpdate()
{
	if (warWeapon->GetActive() == true)return;

	for (int i = 0; i < activeBullets.size(); i++)
	{
		float length = D3DXVec3Length(&(transform->position - activeBullets[i]->transform->position));
		if (length >= bulletRange || activeBullets[i]->GetActive() == false)
		{
			bulletPool->ReleaseObject(activeBullets[i]);
			activeBullets.erase(activeBullets.begin() + i);
		}
	}
}
