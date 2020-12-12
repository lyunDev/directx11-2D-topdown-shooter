#include "stdafx.h"
#include "IonRedMuzzleFlash.h"

IonRedMuzzleFlash::IonRedMuzzleFlash()
	: MuzzleFlash(Vector3(100, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Ion_Red_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
