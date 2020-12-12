#include "stdafx.h"
#include "PlazmaElipseGreenMuzzleFlash.h"

PlazmaElipseGreenMuzzleFlash::PlazmaElipseGreenMuzzleFlash()
	:  MuzzleFlash(Vector3(60, 60, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/PlazmaElipse_Green_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
