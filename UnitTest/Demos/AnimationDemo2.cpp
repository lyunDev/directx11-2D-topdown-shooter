#include "Framework.h"
#include "AnimationDemo2.h"
#include "Geometries/AnimationRect2.h"
void AnimationDemo2::Init()
{
	animationRect = new AnimationRect2({ 100, 100, 0 }, { 100, 100, 1 });

}

void AnimationDemo2::Destroy()
{
	SAFE_DELETE(animationRect);
}

void AnimationDemo2::Update()
{
	animationRect->Update();
}

void AnimationDemo2::PreRender()
{
}

void AnimationDemo2::Render()
{
	animationRect->Render();
}

void AnimationDemo2::GUI()
{
}
