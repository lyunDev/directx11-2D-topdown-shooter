//#include "stdafx.h"
//#include "TestEnemy.h"
//#include "Utilities/RenderTexture.h"
//#include "Effects/Dissolve.h"
//#include "Effects/NormalBlur.h"
//#include "Game/Transform.h"
//#include "ShaderBuffers/ColorBuffer.h"
//#include "AI/FSM/EnemyState.h"
//#include "GameObject/MuzzleFlash.h"
//
////TestEnemy::TestEnemy(Vector3 position, Vector3 size)
////	: Actor(ActorInfo(100, 100), position, size, 0, false)
////{
////	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Pyro.png");
////	SetSRV(tex->GetSRV());
////	SAFE_DELETE(tex);
////	SetRenderToCollisionBox(true);
////	
////	
////	
////	Texture2D * map = new Texture2D(TexturePath + L"dissolveMap.jpg");
////	dissolveMap = map->GetSRV();
////	SAFE_DELETE(map);
////
////	dissolveBuffer = new DissolveBuffer();
////
////	colorBuffer = new ColorBuffer();
////
////	SetTag("Enemy");
////	
////	enemyState = new ThinkingState();
////
////
////	bulletPool = new ObjectPool<Bullet>();
////	muzzleFlash = new MuzzleFlash();
////	firePos = new Transform();
////	muzzlePos = new Transform();
////
////	SetObjectLayer(ObjectLayer::ENEMY);
////	
////}
//
//TestEnemy::TestEnemy()
//	: Actor(ActorInfo(100, 100), Vector3(0, 0, 0), Vector3(100, 100, 1), 0, false)
//{
//	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Pyro.png");
//	SetSRV(tex->GetSRV());
//	SAFE_DELETE(tex);
//	SetRenderToCollisionBox(true);
//
//
//
//	//Texture2D * map = new Texture2D(TexturePath + L"dissolveMap.jpg");
//	//dissolveMap = map->GetSRV();
//	//SAFE_DELETE(map);
//
//	//dissolveBuffer = new DissolveBuffer();
//
//	//colorBuffer = new ColorBuffer();
//
//	SetTag("Enemy");
//
//	enemyState = new ThinkingState();
//
//
//	bulletPool = new ObjectPool<Bullet>();
//	muzzleFlash = new MuzzleFlash();
//	firePos = new Transform();
//	muzzlePos = new Transform();
//
//	SetObjectLayer(ObjectLayer::ENEMY);
//
//	SetActive(false);
//}
//
//TestEnemy::~TestEnemy()
//{
//	SAFE_DELETE(bulletPool);
//	SAFE_DELETE(muzzleFlash);
//	SAFE_DELETE(firePos);
//	SAFE_DELETE(muzzlePos);
//	SAFE_DELETE(enemyState);
//	//SAFE_DELETE(colorBuffer);
//	//SAFE_DELETE(dissolveBuffer);
//
//}
//
//void TestEnemy::OnCollisionEnter(GameObject* other)
//{
//	if (other->GetTag() == "Bullet")
//	{
//		Bullet * bullet = static_cast<Bullet *>(other);
//		if (bullet == nullptr) return;
//		if (bullet->GetOwnerTag() == "Player")
//		{
//			GetColorBuffer()->SetColor(Color(1, 1, 1, 0));
//			actorInfo.Hit(10);
//		}
//	}
//}
//void TestEnemy::OnUpdate()
//{
//	FirePosUpdate();
//	Fire();
//	BulletUpdate();
//
//
//	EnemyState * state = enemyState->Update(this);
//	if (state != nullptr)
//	{
//		enemyState->Exit(this);
//		SAFE_DELETE(enemyState);
//		enemyState = state;
//		enemyState->Enter(this);
//	}
//
//	if (actorInfo.isDie == true)
//	{
//		GetDissolveBuffer()->IncreaseDissolveAmount(1 * Time::Delta());
//		if (GetDissolveBuffer()->GetDissolveAmount() >= 1)
//			SetActive(false);
//	}
//	/*if (actorInfo.isDie == true)
//		SetActive(false);*/
//}
//
//void TestEnemy::OnPreRender()
//{
//
//}
//
//void TestEnemy::OnRender()
//{
//	/*if (actorInfo.isDie)
//	{
//		SetShader(ShaderPath + L"Dissolve.hlsl");
//		DC->PSSetShaderResources(1, 1, &dissolveMap);
//		dissolveBuffer->SetPSBuffer(2);
//	}
//	else
//	{
//		SetShader(ShaderPath + L"TextureWithColor.hlsl");
//		colorBuffer->SetPSBuffer(2);
//	}*/
//
//}
//
//void TestEnemy::OnPostRender()
//{
//	if (GetColorBuffer()->GetColor() == Color(1, 1, 1, 0))
//		GetColorBuffer()->SetColor(Color(0, 0, 0, 0));
//}
//
//void TestEnemy::OnRespawn(Vector3 respawnPos, float respawnRot)
//{
//	Actor::OnRespawn(respawnPos, respawnRot);
//	GetDissolveBuffer()->SetDissolveAmount(0);
//	transform->position = respawnPos;
//	transform->rotation = respawnRot;
//	SetActive(true);
//}
//
//
//void TestEnemy::FirePosUpdate()
//{
//	firePos->position = Vector3(0, 100, 0);
//	firePos->size = transform->size;
//	firePos->Rotate((float)D3DXToRadian(transform->rotation));
//	firePos->position += transform->position;
//	firePos->rotation = transform->rotation;
//
//	muzzlePos->position = Vector3(0, 100, 0);
//	muzzlePos->size = transform->size;
//	muzzlePos->Rotate((float)D3DXToRadian(transform->rotation));
//	muzzlePos->position += transform->position;
//	muzzlePos->rotation = transform->rotation;
//
//
//}
//
//void TestEnemy::Fire()
//{
//	currentShootDelay += Time::Delta();
//	if (currentShootDelay >= shootDelay)
//	{
//		currentShootDelay = 0;
//		if (activeBullets.size() >= bulletMaximum)
//			return;
//
//		auto bullet = bulletPool->AccquireObject();
//		//bullet->SetActive(false);
//		activeBullets.push_back(bullet);
//		bullet->SetOwnerTag("Enemy");
//		bullet->Fire(*firePos);
//		bullet->isHited = false;
//		bullet->SetActive(true);
//
//		
//		muzzleFlash->Fire(*muzzlePos);
//		muzzleFlash->SetActive(true);
//	}
//}
//
//void TestEnemy::BulletUpdate()
//{
//	for (int i = 0; i < activeBullets.size(); i++)
//	{
//		float length = D3DXVec3Length(&(transform->position - activeBullets[i]->transform->position));
//		if (length >= bulletRange || activeBullets[i]->isHited)
//		{
//			activeBullets[i]->SetActive(false);
//			activeBullets[i]->isHited = false;
//			bulletPool->ReleaseObject(activeBullets[i]);
//			activeBullets.erase(activeBullets.begin() + i);
//		}
//
//	}
//}
