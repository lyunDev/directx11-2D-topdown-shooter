#include "stdafx.h"
#include "PlazmaArrowRedMuzzleFlash.h"

PlazmaArrowRedMuzzleFlash::PlazmaArrowRedMuzzleFlash() 
	: MuzzleFlash(Vector3(100, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/PlazmaArrow_Red_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
