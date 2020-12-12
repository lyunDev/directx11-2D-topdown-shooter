#include "stdafx.h"
#include "CrossHair.h"
#include "Game/Transform.h"
#include "Utilities/Layers.h"

CrossHair::CrossHair()
	: GameObject(Vector3(0, 0, 0), Vector3(100, 100, 1), 0, false)
{
	Texture2D * tex = new Texture2D(TexturePath + L"UI/crosshair.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);

	SetTag("UI");

	SetObjectLayer(ObjectLayer::UI);
	SetRenderLayer(RenderLayer::UI);
}



void CrossHair::OnUpdate()
{
	Vector3 mPos = Mouse::Get()->GetPosition();
	Vector3 outpos;
	Camera::Get()->UnProjection(&outpos, mPos, Values::Identity);
	transform->position = outpos;
}


