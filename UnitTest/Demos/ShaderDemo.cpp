#include "stdafx.h"
#include "Geometries/TextureRect.h"
#include "Geometries/ShadedTexture.h"
#include "ShaderDemo.h"

void ShaderDemo::Init()
{
	tr1 = new ShadedTexture(TexturePath + L"AA.jpg", Vector3(620, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f);
	tr1->SetShader(ShaderPath + L"Grayscale.hlsl");
}

void ShaderDemo::Destroy()
{
	SAFE_DELETE(tr1);
}

void ShaderDemo::Update()
{
	tr1->Update();
}

void ShaderDemo::Render()
{
	tr1->Render();
}

void ShaderDemo::PreRender()
{
}

void ShaderDemo::GUI()
{
	tr1->GUI();
}
