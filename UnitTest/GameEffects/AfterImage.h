#pragma once

#include "Game/GameObject.h"

class AfterImage : public GameObject
{
public :
	AfterImage(const Transform * transform);


	virtual void OnUpdate() override;
	virtual void OnPostUpdate() override;
	virtual void OnRender() override;
	void SetAfterImageSRV(ID3D11ShaderResourceView * srv)
	{
		SetSRV(srv);
	}
private :
	//class AlphaBuffer * alphaBuffer = nullptr;
};