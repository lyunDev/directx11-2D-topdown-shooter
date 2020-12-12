#include "stdafx.h"
#include "CharacterDemo.h"
#include "Game/Ataho.h"

void CharacterDemo::Init()
{
	ataho = new Ataho(Vector3(100, 100, 0), Vector3(100, 100, 1));
}

void CharacterDemo::Destroy()
{
	SAFE_DELETE(ataho);
}

void CharacterDemo::Update()
{
	ataho->Update();
}

void CharacterDemo::PreRender()
{
}

void CharacterDemo::Render()
{
	ataho->Render();
}

void CharacterDemo::GUI()
{
}
