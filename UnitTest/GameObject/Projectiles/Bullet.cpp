#include "stdafx.h"
#include "Bullet.h"
#include "Game/Transform.h"
#include "Game/GameObjectManager.h"

Bullet::Bullet(BulletInfo bulletInfo, Vector3 objectSize, Vector3 collisionSize)
	:GameObject(Vector3(0, 0, 0), objectSize, 0, false), bulletInfo(bulletInfo)
{
	collisionTr = new Transform();
	collisionTr->position = transform->position;
	collisionTr->size = collisionSize;
	collisionTr->rotation = transform->rotation;
	SetCollisionTr(&transform->position, &collisionTr->size, &transform->rotation);
	SetActive(false);
	SetTag("Bullet");

	SetRenderLayer(RenderLayer::PROJECTILE);
}



void Bullet::OnUpdate()
{
	currentLiftTime += Time::Delta();
	if (currentLiftTime > lifeTime)
	{
		currentLiftTime = 0;
		SetActive(false);
		return;
	}
	Transform temp;
	temp.position = Vector3(0, bulletInfo.bulletSpd * Time::Delta(), 0);
	temp.Rotate((float)D3DXToRadian(transform->rotation));
	transform->position += temp.position;
}

void Bullet::Fire(Transform * fireTr)
{
	transform->position = fireTr->position;
	transform->rotation = fireTr->rotation;
	SetActive(true);
	GeometryUpdate();
}

void Bullet::OnCollisionEnter(GameObject * other)
{
	GameObject::OnCollisionEnter(other);
	if (other->GetObjectLayer() == ObjectLayer::PLAYER && GetObjectLayer() == ObjectLayer::ENEMY_BULLET)
	{
		SetActive(false);
	}
	if (other->GetObjectLayer() == ObjectLayer::ENEMY && GetObjectLayer() == ObjectLayer::PLAYER_BULLET)
	{
		SetActive(false);
	}
}

void Bullet::OnEnable()
{
}

void Bullet::OnDisable()
{
	currentLiftTime = 0;
}

