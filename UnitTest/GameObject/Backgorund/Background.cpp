#include "stdafx.h"
#include "Background.h"
#include "Utilities/Layers.h"
Background::Background()
	:GameObject(Vector3(0, 0, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0, false)
{
	SetTag("Background");
	SetActive(false);
	SetObjectLayer(ObjectLayer::BACKGROUND);
	SetRenderLayer(RenderLayer::BACKGROUND);
}

