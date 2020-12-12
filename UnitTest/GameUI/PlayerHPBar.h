#pragma once

#include "UI/Pannel.h"

class PlayerHPBar : public Pannel
{
public :
	PlayerHPBar(Vector3 position, Vector3 size);
	virtual ~PlayerHPBar();
	void SetPlayer(GameObject * player);
	virtual void OnUpdate() override;
	virtual void OnRender() override;
private :
	class ProgressBuffer * progressBuffer;
	class ActorInfo * actorInfo;
	class GameObject * owner;
	ID3D11ShaderResourceView * backgroundSRV;  // slot 3
	float progressAmount = 1; // 0 ~ 1
};