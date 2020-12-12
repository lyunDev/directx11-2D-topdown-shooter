#include "Framework.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(wstring filePath, Vector3 position, Vector3 size)
	: UIElement(filePath, position, size,false)
{

}

ProgressBar::~ProgressBar()
{
}
