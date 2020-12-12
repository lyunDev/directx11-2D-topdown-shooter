#include "stdafx.h"
#include "GasGreenMuzzleFlash.h"

GasGreenMuzzleFlash::GasGreenMuzzleFlash()
	: MuzzleFlash(Vector3(100, 80, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Gas_Green_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
