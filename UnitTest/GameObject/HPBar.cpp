#include "stdafx.h"
#include "HPBar.h"
#include "ShaderBuffers/ProgressBuffer.h"
#include "GameObject/Actor.h"
#include "Game/Transform.h"
HPBar::HPBar(GameObject * owner, ActorInfo * info, bool isPlayer)
	: GameObject(Vector3(0, 0, 0), Vector3(80, 20, 1), 0, false)
{
	this->owner = owner;
	this->actorInfo = info;
	SetShader(ShaderPath + L"ProgressBar.hlsl");
	Texture2D * progressTex = nullptr;
	progressBuffer = new ProgressBuffer();
	if (isPlayer)
		progressTex = new Texture2D(TexturePath + L"UI/GreenBar.png");
	else
		progressTex = new Texture2D(TexturePath + L"UI/RedBar.png");
	SetSRV(progressTex->GetSRV());
	
	Texture2D * backgroundTex = new Texture2D(TexturePath + L"UI/EmptyBar.png");
	backgroundSRV = backgroundTex->GetSRV();

	SetObjectLayer(ObjectLayer::UI);
	SetRenderLayer(RenderLayer::UI);
}

HPBar::~HPBar()
{
	SAFE_DELETE(progressBuffer);
}

void HPBar::OnUpdate()
{
	AlignPos();
	UpdateProgress();
}

void HPBar::OnRender()
{
	DC->PSSetShaderResources(3, 1, &backgroundSRV);
	progressBuffer->SetPSBuffer(6);
}

void HPBar::AlignPos()
{
	if (owner == nullptr)
	{
#ifdef _DEBUG
		cout << "warning hpbar.cpp, AlignPos" << endl;
#endif
		return;
	}
	Vector3 offset = Vector3(0, -60, 0);
	transform->position = owner->transform->position + offset;

}

void HPBar::UpdateProgress()
{
	if (actorInfo == nullptr)
	{
#ifdef _DEBUG
		cout << "warning hpbar.cpp, UpdateProgress" << endl;
#endif
		return;
	}
	if (progressBuffer->GetProcessAmount() <= 0 || actorInfo->currentHp <= 0)
	{
		progressBuffer->SetProcessAmount(0);
		return;
	}
	else
		progressBuffer->SetProcessAmount((float)actorInfo->currentHp / actorInfo->maxHp);

}
