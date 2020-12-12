//#pragma once
//#include "Game/GameObject.h"
//#include "Game/Transform.h"
//
//class Bullet : public GameObject
//{
//public :
//
//	Bullet();
//	virtual ~Bullet();
//	virtual void OnUpdate() override;
//	void Fire(Transform fireTr);
//	virtual void OnCollisionStay(GameObject* other) override;
//	virtual void OnCollisionEnter(GameObject * other) override;
//
//	virtual void OnEnable() override;
//	virtual void OnDisable() override;
//	bool isHited = false;
//	void SetOwnerTag(string tag);
//	string GetOwnerTag()
//	{
//		return ownerTag;
//	}
//private :
//	//Transform * collisionTr;
//	string ownerTag = "default";
//	float bulletSpd = 1000;
//};