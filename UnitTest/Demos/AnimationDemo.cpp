#include "Framework.h"
#include "AnimationDemo.h"
#include "Geometries/AnimationRect.h"
void AnimationDemo::Init()
{
	animationRect = new AnimationRect({ 100, 100, 0 }, {100, 100, 1});
	
}

void AnimationDemo::Destroy()
{
	SAFE_DELETE(animationRect);
}

void AnimationDemo::Update()
{
	animationRect->Update();
}

void AnimationDemo::PreRender()
{
}

void AnimationDemo::Render()
{
	animationRect->Render();
}

void AnimationDemo::GUI()
{
}
