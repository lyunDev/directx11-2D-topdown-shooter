#include "Framework.h"
#include "ShaderFilterDemo.h"
#include "Geometries/TextureFilterRect.h"

void ShaderFilterDemo::Init()
{
	tr1 = new TextureFilterRect(TexturePath + L"AA.jpg", Vector3(620, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f);
}

void ShaderFilterDemo::Destroy()
{
	SAFE_DELETE(tr1);
}

void ShaderFilterDemo::Update()
{
	tr1->Update();
}

void ShaderFilterDemo::Render()
{
	tr1->Render();
}

void ShaderFilterDemo::PreRender()
{

}

void ShaderFilterDemo::GUI()
{
	tr1->GUI();
}
