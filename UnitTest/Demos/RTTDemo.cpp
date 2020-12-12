#include "stdafx.h"
#include "RTTDemo.h"

#include "Geometries/Rect.h"
#include "Geometries/TextureRect.h"
#include "Utilities/RenderTexture.h"

void RTTDemo::Init()
{
	rtt = new RenderTexture();
	r = new Rect(Vector3(200, 200, 0), Vector3(100, 100, 1), 0);
	r2 = new Rect(Vector3(500, 400, 0), Vector3(100, 100, 1), 0);
	r3 = new Rect(Vector3(700, 100, 0), Vector3(100, 100, 1), 0);
	rt2 = new TextureRect(Vector3(WinMaxWidth - (WinMaxWidth / 4), WinMaxHeight - (WinMaxHeight / 4), 0), Vector3(WinMaxWidth / 4, WinMaxHeight / 4, 1));
	rt1 = new TextureRect(TexturePath + L"AA.jpg", Vector3( 100, 100, 0 ), Vector3(100, 100 ,1), 0);
	rt2->SetShader(ShaderPath + L"Minimap.hlsl");
}

void RTTDemo::Destroy()
{
	SAFE_DELETE(rt2);
	SAFE_DELETE(rtt);
	SAFE_DELETE(r);

}

void RTTDemo::Update()
{
	r->Update();
	rt1->Update();
	rt2->Update();
	r->Move();
	r2->Update();
	r3->Update();
}

void RTTDemo::PreRender()
{
	Graphics::Get()->InitViewport();
	rtt->RenderToTexture();
	{
		r->Render();
		r2->Render();
		r3->Render();
		rt1->Render();
	}


}

void RTTDemo::Render()
{
	r->Render();
	r2->Render();
	r3->Render();
	rt1->Render();

	rt2->SetSRV(rtt->GetSRV());
	rt2->Render();
}

void RTTDemo::GUI()
{

}
