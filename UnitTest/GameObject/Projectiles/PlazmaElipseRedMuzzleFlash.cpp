#include "stdafx.h"
#include "PlazmaElipseRedMuzzleFlash.h"

PlazmaElipseRedMuzzleFlash::PlazmaElipseRedMuzzleFlash()
	: MuzzleFlash(Vector3(60, 60, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/PlazmaElipse_Red_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
