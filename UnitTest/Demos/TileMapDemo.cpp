#include "stdafx.h"
#include "TileMapDemo.h"
#include "Geometries/TileMap.h"

void TileMapDemo::Init()
{
	uint spacing = 40;
	uint width = WinMaxWidth / spacing;
	uint height = WinMaxHeight / spacing;
	tm = new TileMap(width, height, spacing);
}

void TileMapDemo::Destroy()
{
	SAFE_DELETE(tm);
}

void TileMapDemo::Update()
{
	tm->Update();
}

void TileMapDemo::PreRender()
{
}

void TileMapDemo::Render()
{
	tm->Render();
}

void TileMapDemo::GUI()
{
	tm->GUI();
}
