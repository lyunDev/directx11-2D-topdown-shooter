#include "stdafx.h"
#include "BlurDemo.h"


#include "Geometries/BlurredTexture.h"


void BlurDemo::Init()
{
	bt = new BlurredTexture(TexturePath + L"AA.jpg", Vector3(620, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f);
	bt->SetShader(ShaderPath + L"Blur.hlsl");
}

void BlurDemo::Destroy()
{
	SAFE_DELETE(bt);
}

void BlurDemo::Update()
{
	bt->Update();
}

void BlurDemo::PreRender()
{
}

void BlurDemo::Render()
{
	bt->Render();
}

void BlurDemo::GUI()
{
	bt->GUI();
}
