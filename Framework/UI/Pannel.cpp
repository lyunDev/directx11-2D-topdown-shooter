#include "Framework.h"
#include "Pannel.h"

Pannel::Pannel(wstring filePath, Vector3 position, Vector3 size, bool hasAnimation)
	: UIElement(filePath, position, size, hasAnimation)
{
}

Pannel::Pannel(Vector3 position, Vector3 size, bool hasAnimation)
	: UIElement(position, size, hasAnimation)
{

}
