#include "Framework.h"
#include "Player.h"
#include "Geometries/TextureRect.h"
#include "Game/Transform.h"
#include "GameObject/MuzzleFlash.h"
#include "GameEffects/AfterImage.h"
#include "GameEffects/BoostEffect.h"
#include "Utilities/Layers.h"
#include "GameObject/HPBar.h"
#include "ShaderBuffers/ColorBuffer.h"
#include "GameObject/BulletRemoveEffect.h"
#include "Game/GameObjectManager.h"
#include "Event/EventDispatcher.h"
#include "Event/EventTypes.h"
#include "GameObject/LevelUpEffect.h"
#include "GameUI/BossCautionPannel.h"
#include "GameObject/Skills/Shield.h"
#include "GameObject/Skills/WideExplosion.h"
#include "UI/Pannel.h"
#include "Effects/Dissolve.h"


Player::Player(Vector3 position, Vector3 size)
	: Actor(ActorInfo(100, 100),position, size, 0, false)
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Player.png");
	SetSRV(tex->GetSRV());
	machineGunModeSRV = tex->GetSRV();

	Texture2D * canonTex = new Texture2D(TexturePath + L"GameObject/HeavyGunner_Canon.png");
	canonGunModeSRV = canonTex->GetSRV();

	SAFE_DELETE(tex);


	firePos = new Transform();
	muzzlePos = new Transform();
	leftBoostPos = new Transform();
	rightBoostPos = new Transform();
	//hpBar = new HPBar(this, &actorInfo, true);
	Camera::Get()->SetTarget(&this->transform->position);


	SetRenderToCollisionBox(true);

	SetTag("Player");
	machineGunBulletPool = new ObjectPool<NormalBullet>();
	canonGunBulletPool = new ObjectPool<PlayerPlazmaBullet>();
	SetRenderLayer(RenderLayer::GAMEOBJECT);

	//muzzleFlash = new MuzzleFlash();
	machineGunMuzzleFlash = make_shared<NormalMuzzleFlash>();
	canonGunMuzzleFlash = make_shared<PlayerPlazmaMuzzleFlash>();
	//leftBoostEffect = new BoostEffect();
	//rightBoostEffect = new BoostEffect();

	SetObjectLayer(ObjectLayer::PLAYER);

	collisionTr = new Transform();
	collisionTr->position = transform->position;
	collisionTr->size = Vector3(60, 60, 1);
	collisionTr->rotation = transform->rotation;
	SetCollisionTr(&transform->position, &collisionTr->size, &transform->rotation);

	maxLevel = expTable.size() - 1;
	EventDispatcher::AddEventListener(BattleEvent::KillEnemy, [&]() 
	{
		exp += 10;
		if (exp >= expTable[level] && level != maxLevel)
		{
			level++;
			LevelUp();
		}
	});

	shield = new Shield(this, Vector3(150, 150, 1), shieldEnergy);

	machineGunUI = new Pannel(TexturePath + L"UI/heavygun.png", Vector3(WinMaxWidth - 130, 150, 0), Vector3(150, 200, 1), false);
	 canonGunUI = new Pannel(TexturePath + L"UI/luncher.png", Vector3(WinMaxWidth - 130, 150, 0), Vector3(150, 200, 1), false);
	 machineGunUI->SetActive(true);
	 canonGunUI->SetActive(false);

}

Player::~Player()
{

	SAFE_DELETE(leftBoostPos);
	SAFE_DELETE(rightBoostPos);
	SAFE_DELETE(firePos);
	SAFE_DELETE(machineGunBulletPool);

	SAFE_DELETE(muzzlePos);
}

void Player::OnUpdate()
{
	ChangeAttackMode();
	PlayerMove();
	PlayerRotate();
	FirePosUpdate();
	Fire();
	SlowUpdate();
	BoostUpdate();
	ShieldUpdate();
	ActiveShield();
	WideExplosionSkill();

	if (actorInfo.isDie)
	{
		GetDissolveBuffer()->IncreaseDissolveAmount(Time::Delta());
		if (GetDissolveBuffer()->GetDissolveAmount() >= 1)
		{
			SetActive(false);
			EventDispatcher::TriggerEvent(GameEvent::PlayerDie);
		}
	}
}

void Player::OnPostUpdate()
{
	leftMoveStop = false;
	rightMoveStop = false;
	upMoveStop = false;
	downMoveStop = false;

	BulletUpdate();
}

void Player::OnCollisionStay(GameObject * other)
{
	GameObject::OnCollisionStay(other);
	if (other->GetTag() == "Enemy")
	{
		float xDistance = std::abs(transform->position.x - other->transform->position.x);
		float yDistance = std::abs(transform->position.y - other->transform->position.y);
		if (xDistance - transform->size.x * 0.5f <= other->transform->size.x * 0.5f && yDistance - transform->size.y * 0.5f <= other->transform->size.y * 0.5f)
		{
			if (other->transform->position.x > transform->position.x)
				rightMoveStop = true;
			else if (other->transform->position.x <= transform->position.x)
				leftMoveStop = true;
			if (other->transform->position.y > transform->position.y)
				upMoveStop = true;
			else if (other->transform->position.y <= transform->position.y)
				downMoveStop = true;
		}
	}
}

void Player::OnCollisionEnter(GameObject * other)
{
	GameObject::OnCollisionEnter(other);
	if (other->GetObjectLayer() == ObjectLayer::ENEMY_BULLET)
	{
		Bullet * bullet = static_cast<Bullet *>(other);
		if (bullet == nullptr) return;
		Hit(bullet->GetBulletInfo().damage);

	}
}

void Player::OnPostRender()
{
	if (GetColorBuffer()->GetColor() == Color(1, 1, 1, 0))
		GetColorBuffer()->SetColor(Color(0, 0, 0, 0));
}

void Player::Hit(float damage)
{
	if (bActiveShield)
	{
		shield->HitShield(damage);
	}
	else
	{
		GetColorBuffer()->SetColor(Color(1, 1, 1, 0));
		actorInfo.Hit(damage);
	}
}

void Player::Delete()
{
	GameObject::Delete();
	
	shield->Delete();
	//hpBar->Delete();
}


void Player::PlayerMove()
{
	if (Keyboard::Get()->Press('A') && !leftMoveStop)
	{	
		transform->position.x -= playerSpeed * Time::Delta();
	}
	if (Keyboard::Get()->Press('D') && !rightMoveStop)
	{
		transform->position.x += playerSpeed * Time::Delta();
	}
	if (Keyboard::Get()->Press('W') && !upMoveStop)
	{
		transform->position.y += playerSpeed * Time::Delta();
	}
	if (Keyboard::Get()->Press('S') && !downMoveStop)
	{
		transform->position.y -= playerSpeed * Time::Delta();
	}


}

void Player::PlayerRotate()
{
		Vector3 mPos = Mouse::Get()->GetPosition();
		Vector3 outpos;
		Camera::Get()->UnProjection(&outpos, mPos, Values::Identity);
		outpos.z = 0.0f;
		float rot = DxMath::GetAngle(Values::UpVec, outpos - transform->position);
		transform->rotation = rot;
		
}

void Player::FirePosUpdate()
{
	if (bMachineGunMode)
	{
		firePos->position = Vector3(-5, 30, 0);
		firePos->size = transform->size;
		firePos->Rotate((float)D3DXToRadian(transform->rotation));
		firePos->position += transform->position;
		firePos->rotation = transform->rotation;

		muzzlePos->position = Vector3(-5, 90, 0);
		muzzlePos->size = transform->size;
		muzzlePos->Rotate((float)D3DXToRadian(transform->rotation));
		muzzlePos->position += transform->position;
		muzzlePos->rotation = transform->rotation;
	}
	else // canongun mode
	{
		firePos->position = Vector3(-5, 50, 0);
		firePos->size = transform->size;
		firePos->Rotate((float)D3DXToRadian(transform->rotation));
		firePos->position += transform->position;
		firePos->rotation = transform->rotation;

		muzzlePos->position = Vector3(-5, 70, 0);
		muzzlePos->size = transform->size;
		muzzlePos->Rotate((float)D3DXToRadian(transform->rotation));
		muzzlePos->position += transform->position;
		muzzlePos->rotation = transform->rotation;
	}
}

void Player::ShieldUpdate()
{
	if (shield->GetActive() == false)
		bActiveShield = false;
}

void Player::Fire()
{
	machineGunCurrentShootDelay += Time::Delta();
	canonGunCurrentShootDelay += Time::Delta();
	if (Mouse::Get()->Press(0))
	{
		if (machineGunCurrentShootDelay >= machineGunShootDelay)
		{
			machineGunCurrentShootDelay = 0;
			if (machineGunActiveBullets.size() >= machineGunBulletMaximum)
				return;
			auto bullet = machineGunBulletPool->AccquireObject();
			machineGunActiveBullets.push_back(bullet);
			bullet->Fire(firePos);
			
			machineGunMuzzleFlash->Flash(muzzlePos);

			Camera::Get()->Shake(0.1f, 2.0f);
		}
	}
	if (Mouse::Get()->Press(1))
	{
		if (canonGunCurrentShootDelay >= canonGunShootDelay)
		{
			canonGunCurrentShootDelay = 0;
			if (canonGunActiveBullets.size() >= canonGunBulletMaximum)
				return;
			auto bullet = canonGunBulletPool->AccquireObject();
			canonGunActiveBullets.push_back(bullet);
			bullet->Fire(firePos);

			canonGunMuzzleFlash->Flash(muzzlePos);
		}
	}
}

void Player::BulletUpdate()
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
	if (bMachineGunMode)
	{
		for (int i = 0; i < machineGunActiveBullets.size(); i++)
		{
			float length = D3DXVec3Length(&(transform->position - machineGunActiveBullets[i]->transform->position));
			if (length >= machineGunBulletRange || machineGunActiveBullets[i]->GetActive() == false)
			{
				machineGunBulletPool->ReleaseObject(machineGunActiveBullets[i]);
				machineGunActiveBullets.erase(machineGunActiveBullets.begin() + i);
			}
		}
	}
}
void Player::ActiveShield()
{
	if (Keyboard::Get()->Down('R'))
	{
		if (bActiveShield == false)
		{
			bActiveShield = true;
		
			shield->ActiveShield();
		}
	}
}
void Player::SlowUpdate()
{
	if (Keyboard::Get()->Press(VK_SPACE))
	{
		Time::Get()->SetTimeScale(0.3f);
		playerSpeed = 200;
		currentAfterImageDelay += Time::Delta();
		if (currentAfterImageDelay >= afterImageDelay)
		{
			currentAfterImageDelay = 0;

			AfterImage * afterImage = new AfterImage(transform);
			afterImage->SetAfterImageSRV(GetSRV());
		}
	}
	else
	{
		playerSpeed = 100;
		Time::Get()->SetTimeScale(1);
		currentAfterImageDelay = afterImageDelay;
	}
}


void Player::BoostUpdate()
{
	
	/*if (Keyboard::Get()->Press(VK_SHIFT))
	{
		float xPos = 0;
		float yPos = 0;
		if (Keyboard::Get()->Press('A') && !leftMoveStop)
		{
			xPos -= playerSpeed * Time::Delta();
		}
		if (Keyboard::Get()->Press('D') && !rightMoveStop)
		{
			xPos += playerSpeed * Time::Delta();
		}
		if (Keyboard::Get()->Press('W') && !upMoveStop)
		{
			yPos += playerSpeed * Time::Delta();
		}
		if (Keyboard::Get()->Press('S') && !downMoveStop)
		{
			yPos -= playerSpeed * Time::Delta();
		}
		if (xPos != 0 || yPos != 0)
		{
			Vector3 lookAt = Vector3(xPos, yPos, 0);
			float angle = DxMath::GetAngle(Values::UpVec, lookAt);
			transform->rotation = angle;
		}
		
		playerSpeed = 300;
	}
	else
	{
		playerSpeed = 100;

	}
	leftBoostPos->position = Vector3(-15, 100, 0);
	leftBoostPos->size = transform->size;
	leftBoostPos->Rotate((float)D3DXToRadian(transform->rotation + 180));
	leftBoostPos->position += transform->position;
	leftBoostPos->rotation = transform->rotation + 180;

	rightBoostPos->position = Vector3(15, 100, 0);
	rightBoostPos->size = transform->size;
	rightBoostPos->Rotate((float)D3DXToRadian(transform->rotation + 180));
	rightBoostPos->position += transform->position;
	rightBoostPos->rotation = transform->rotation + 180;
	if (Keyboard::Get()->Down(VK_SHIFT))
	{
		

		leftBoostEffect->SetTr(leftBoostPos);
		leftBoostEffect->SetActive(true);

		rightBoostEffect->SetTr(rightBoostPos);
		rightBoostEffect->SetActive(true);


	}*/
}

void Player::BulletRemoveSkill()
{
	/*if (Keyboard::Get()->Down('R'))
	{*/
		BulletRemoveEffect * effect = new BulletRemoveEffect();
		effect->Explode(transform);
		auto bullets = GameObjectManager::Get()->FindObjectsWithDistance(this, WinMaxWidth, ObjectLayer::ENEMY_BULLET);
		for (auto bullet : bullets)
		{
			bullet->SetActive(false);
		}

	
	//}
}

void Player::WideExplosionSkill()
{
	if (Keyboard::Get()->Down('T'))
	{
		WideExplosion * effect = new WideExplosion();
		effect->Explode(transform);
		auto bullets = GameObjectManager::Get()->FindObjectsWithDistance(this, WinMaxWidth, ObjectLayer::ENEMY_BULLET);
		for (auto bullet : bullets)
		{
			bullet->SetActive(false);
		}
		auto enemies = GameObjectManager::Get()->FindObjectsWithDistance(this, WinMaxWidth, ObjectLayer::ENEMY);
		for (auto enemy : enemies)
		{
			Actor * actor =static_cast<Actor*>( enemy);
			assert(actor != nullptr);
			actor->Hit(100);
		}

	}
}

void Player::LevelUp()
{
	LevelUpEffect * levelUpEffect = new LevelUpEffect();
	levelUpEffect->LevelUp(transform);
	BulletRemoveSkill();
}

void Player::ChangeAttackMode()
{

	if (Mouse::Get()->Press(0))
	{
		if (bMachineGunMode == false)
		{
			bMachineGunMode = true;
			SetSRV(machineGunModeSRV);
			transform->size = Vector3(100, 100, 1);
			machineGunUI->SetActive(true);
			canonGunUI->SetActive(false);
		}
	}
	if (Mouse::Get()->Press(1))
	{
		if (bMachineGunMode == true)
		{
			bMachineGunMode = false;
			SetSRV(canonGunModeSRV);
			transform->size = Vector3(100, 120, 1);
			machineGunUI->SetActive(false);
			canonGunUI->SetActive(true);
		}
	}

}


