#pragma once
#include "Actor.h"
#include "Game/GameObject.h"

class RespawnShip : public Actor
{
public :
	RespawnShip(Vector3 position, Vector3 size);
	virtual ~RespawnShip();

	virtual void OnCollisionEnter(GameObject* other) override;
	virtual void OnUpdate() override;
	virtual void OnPreRender() override;
	virtual void OnRender() override;

private :

};