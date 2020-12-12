#include "stdafx.h"
#include "WarWeapon.h"
#include "Player.h"
#include "Game/Transform.h"
#include "GameObject/MuzzleFlash.h"
#include "Game/GameObjectManager.h"
#include "ShaderBuffers/ColorBuffer.h"
#include "Effects/Dissolve.h"
#include "GameObject/Projectiles/Bullet.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"

WarWeapon::WarWeapon(Vector3 position, Vector3 size, WarWeaponType warWeaponType)
	:Actor(ActorInfo(100, 100), position, size, 0, false)
{
	Texture2D * tex = nullptr;
	switch (warWeaponType)
	{
	case WarWeaponType::Gun1_1 :
		break;
	case WarWeaponType::Gun1_2 :
		break;
	case WarWeaponType::Gun1_3 :
		break;
	case WarWeaponType::Gun1_4 :
		break;
	case WarWeaponType::Gun2 :
		break;
	case WarWeaponType::Gun3_1 :
		break;
	case WarWeaponType::Gun3_2 :
		tex = new Texture2D(TexturePath + L"GameObject/WarMachines/Gun3_2.png");
		break;
	}
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	player = GameObjectManager::Get()->GetPlayer();
	fixedPos = transform->position;

	bulletPool = new ObjectPool<WarWeaponBullet>();
	muzzleFlash = new WarWeaponMuzzleFlash();

	firePos = new Transform();
	muzzlePos = new Transform();

	SetObjectLayer(ObjectLayer::ENEMY);
	SetRenderLayer(RenderLayer::GAMEOBJECT);

	/*colorBuffer = new ColorBuffer();
	dissolveBuffer = new DissolveBuffer();

	Texture2D * map = new Texture2D(TexturePath + L"dissolveMap.jpg");
	dissolveMap = map->GetSRV();
	SAFE_DELETE(map);*/

	//SetShader(ShaderPath + L"TextureWithColor.hlsl");
}

WarWeapon::~WarWeapon()
{
	//SAFE_DELETE(dissolveBuffer);
	SAFE_DELETE(firePos);
	SAFE_DELETE(muzzlePos);
	SAFE_DELETE(bulletPool);
	SAFE_DELETE(muzzleFlash);
	
}

void WarWeapon::OnUpdate()
{
	Vector3 targetPos = player->transform->position;
	float rot = DxMath::GetAngle(Values::UpVec, targetPos - transform->position);

	Transform tr;
	tr.position = Vector3(0, 100, 0);
	tr.Rotate((float)D3DXToRadian(rot));
	tr.position += fixedPos;
	
	transform->position = tr.position;
	transform->rotation = rot;

	FirePosUpdate();
	Fire();
	BulletUpdate();


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

void WarWeapon::OnRender()
{
	/*if (actorInfo.isDie == true)
	{
		SetShader(ShaderPath + L"Dissolve.hlsl");
		DC->PSSetShaderResources(1, 1, &dissolveMap);
		dissolveBuffer->SetPSBuffer(2);
	}
	else
	{
		colorBuffer->SetPSBuffer(2);
	}*/
}

void WarWeapon::OnPostRender()
{
	if (GetColorBuffer()->GetColor() == Color(1, 1, 1, 0))
		GetColorBuffer()->SetColor(Color(0, 0, 0, 0));
}

void WarWeapon::OnCollisionEnter(GameObject * other)
{
	/*if (other->GetTag() == "Bullet")
	{
		Bullet * bullet = static_cast<Bullet *>(other);
		if (bullet == nullptr) return;
		if (bullet->GetOwnerTag() == "Player")
		{
			GetColorBuffer()->SetColor(Color(1, 1, 1, 0));
			actorInfo.Hit(10);
		}
	}*/
	GameObject::OnCollisionEnter(other);
	if (other->GetObjectLayer() == ObjectLayer::PLAYER_BULLET)
	{
		Bullet * bullet = static_cast<Bullet *>(other);
		if (bullet == nullptr) return;
		Hit(bullet->GetBulletInfo().damage);
	}

}
void WarWeapon::OnRespawn(Vector3 respawnPos, float respawnRot)
{
	Actor::OnRespawn(respawnPos, respawnRot);
	GetDissolveBuffer()->SetDissolveAmount(0);
	transform->position = respawnPos;
	transform->rotation = respawnRot;
	fixedPos = transform->position;
	SetActive(true);
}

void WarWeapon::Hit(float damage)
{
	GetColorBuffer()->SetColor(Color(1, 1, 1, 0));
	actorInfo.Hit(damage);
}

void WarWeapon::FirePosUpdate()
{
	firePos->position = Vector3(0, 250, 0);
	firePos->size = transform->size;
	firePos->Rotate((float)D3DXToRadian(transform->rotation));
	firePos->position += transform->position;
	firePos->rotation = transform->rotation;

	muzzlePos->position = Vector3(0, 250, 0);
	muzzlePos->size = transform->size;
	muzzlePos->Rotate((float)D3DXToRadian(transform->rotation));
	muzzlePos->position += transform->position;
	muzzlePos->rotation = transform->rotation;
}

void WarWeapon::Fire()
{

	currentShootDelay += Time::Delta();
	if (currentShootDelay >= shootDelay)
	{
		//currentShootDelay = 0;
		currentRpm += Time::Delta();
		if (currentRpm > rpm)
		{
			currentRpm = 0;
			currentShootCount++;
			if (currentShootCount > shootCount)
			{
				currentShootCount = 0;
				currentShootDelay = 0;
			}
			if (activeBullets.size() >= bulletMaximum)
				return;
			auto bullet = bulletPool->AccquireObject();
			activeBullets.push_back(bullet);
			bullet->Fire(firePos);

			muzzleFlash->Flash(muzzlePos);
		}
	}
}

void WarWeapon::BulletUpdate()
{
	/*for (int i = 0; i < activeBullets.size(); i++)
	{
		float length = D3DXVec3Length(&(transform->position - activeBullets[i]->transform->position));
		if (length >= bulletRange || activeBullets[i]->isHited)
		{
			activeBullets[i]->SetActive(false);
			activeBullets[i]->isHited = false;
			bulletPool->ReleaseObject(activeBullets[i]);
			activeBullets.erase(activeBullets.begin() + i);
		}
	}*/
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
