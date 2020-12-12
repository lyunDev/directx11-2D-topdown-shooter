#include "Framework.h"

#include "TextureDemo.h"
#include "Geometries/TextureRect.h"


// RTT
// Render To Texture ±â¹ý



void TextureDemo::Init()
{
	tr1 = new TextureRect(TexturePath + L"AA.jpg", Vector3(620, 360, 0), Vector3(WinMaxWidth, WinMaxHeight, 1), 0.0f);

	tr2 = new TextureRect(Vector3(100, 100, 0), Vector3(100, 100, 1));
	tr3 = new TextureRect(Vector3(300, 300, 0), Vector3(150, 150, 1));

	Texture2D* tex = new Texture2D(TexturePath + L"test.png");
	vector<Color> colors;
	tex->ReadPixel(&colors);

	tr2->SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}

void TextureDemo::Destroy()
{
	SAFE_DELETE(tr1);
	SAFE_DELETE(tr2);
	SAFE_DELETE(tr3);
}

void TextureDemo::Update()
{
	tr1->Update();
	tr2->Update();
	tr3->Update();
}

void TextureDemo::Render()
{
	tr1->Render();
	tr2->Render();
	tr3->Render();
}

void TextureDemo::PreRender()
{

}

void TextureDemo::GUI()
{
}
