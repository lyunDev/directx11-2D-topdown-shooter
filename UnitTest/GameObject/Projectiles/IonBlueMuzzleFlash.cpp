#include "stdafx.h"
#include "IonBlueMuzzleFlash.h"

IonBlueMuzzleFlash::IonBlueMuzzleFlash()
	: MuzzleFlash(Vector3(100, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Ion_Blue_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
