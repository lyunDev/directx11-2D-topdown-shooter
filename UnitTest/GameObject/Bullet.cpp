#include "stdafx.h"
#include "Bullet.h"
#include "Game/Transform.h"

Bullet::Bullet()
	: GameObject(Vector3(0, 0, 0), Vector3(10, 300, 1),0, false)
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/NormalBullet.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	collisionTr = new Transform();
	collisionTr->position = transform->position;
	collisionTr->size = Vector3(20, 100, 1);
	collisionTr->rotation = transform->rotation;
	SetCollisionTr(&transform->position, &collisionTr->size, &transform->rotation);
	//SetCollisionSize(Vector3(20, 100, 1));
	SetActive(false);
	SetTag("Bullet");
	SetRenderToCollisionBox(true);

	SetRenderLayer(RenderLayer::PROJECTILE);
	SetObjectLayer(ObjectLayer::BULLET);
}

Bullet::~Bullet()
{
	int a = 10;
}

void Bullet::OnUpdate()
{
	Transform temp;
	temp.position = Vector3(0, bulletSpd * Time::Delta(), 0);
	temp.Rotate((float)D3DXToRadian(transform->rotation));
	transform->position += temp.position;
}

void Bullet::Fire(Transform fireTr)
{
	transform->position = fireTr.position;
	transform->size = Vector3(30, 100, 0);
	transform->rotation = fireTr.rotation;
}

void Bullet::OnCollisionStay(GameObject* other)
{
	//isHited = true;
	//transform->position.x += 100;
	/*if(transform->size.y > 0)
		transform->size.y-= 1000 *  Time::Delta();
	if (transform->size.y <= 0)
		isHited = true;*/
	/*if(transform->size.y > 0)
		transform->size.y -= 1 * Time::Delta();*/
	/*cout << "충돌" << endl;
	cout << other->transform->position.x << ", " << other->transform->position.y << "," << other->transform->position.z <<  endl;
	cout << other->transform->size.x << ", " << other->transform->size.y << ", " << other->transform->size.z << endl;
	cout << transform->position.x << ", " << transform->position.y << ", " << transform->position.z << endl;
	cout << transform->size.x << ", " << transform->size.y << ", " << transform->size.z << endl;*/
}

void Bullet::OnCollisionEnter(GameObject * other)
{
	if (other->GetTag() == "Player" && ownerTag == "Enemy" || other->GetTag() == "Enemy" && ownerTag == "Player")
	{
		//SetActive(false);
		isHited = true;
	}

}

void Bullet::OnEnable()
{
}

void Bullet::OnDisable()
{
	// 임시 코드
	transform->position.x = Camera::Get()->GetPos().x  -10000;
}

void Bullet::SetOwnerTag(string tag)
{
	ownerTag = tag;
}
