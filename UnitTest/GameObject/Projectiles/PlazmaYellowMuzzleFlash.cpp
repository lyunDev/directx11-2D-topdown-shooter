#include "stdafx.h"
#include "PlazmaYellowMuzzleFlash.h"

PlazmaYellowMuzzleFlash::PlazmaYellowMuzzleFlash()
	: MuzzleFlash(Vector3( 100, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Plazma_Yellow_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
