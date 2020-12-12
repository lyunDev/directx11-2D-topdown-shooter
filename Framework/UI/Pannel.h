#pragma once
#include "UIElement.h"

class Pannel : public UIElement
{
public :
	Pannel(wstring filePath, Vector3 position, Vector3 size, bool hasAnimation);
	Pannel(Vector3 position, Vector3 size, bool hasAnimation);
};