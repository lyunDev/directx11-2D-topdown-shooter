#include "stdafx.h"
#include "RespawnShip.h"

RespawnShip::RespawnShip(Vector3 position, Vector3 size)
	: Actor(ActorInfo(100, 100), position, size, 0, false)
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/RespawnShip.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
	SetRenderToCollisionBox(true);


}

RespawnShip::~RespawnShip()
{
}

void RespawnShip::OnCollisionEnter(GameObject* other)
{
}

void RespawnShip::OnUpdate()
{
}

void RespawnShip::OnPreRender()
{
}

void RespawnShip::OnRender()
{
}
