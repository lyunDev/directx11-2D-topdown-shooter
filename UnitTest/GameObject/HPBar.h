#pragma once

#include "Game/GameObject.h"

class ActorInfo;
class HPBar : public GameObject
{
public :
	HPBar(GameObject * owner, ActorInfo * info, bool isPlayer);
	virtual ~HPBar();

	virtual void OnUpdate() override;
	virtual void OnRender() override;
	void AlignPos();
	void UpdateProgress();
private :
	class ProgressBuffer * progressBuffer;
	class ActorInfo * actorInfo;
	class GameObject * owner;
	ID3D11ShaderResourceView * backgroundSRV; // slot 3
	float progressAmount = 1;// 0 ~ 1
};