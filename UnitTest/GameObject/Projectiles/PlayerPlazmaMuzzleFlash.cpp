#include "stdafx.h"
#include "PlayerPlazmaMuzzleFlash.h"

PlayerPlazmaMuzzleFlash::PlayerPlazmaMuzzleFlash()
	: MuzzleFlash(Vector3(100, 100, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/Plazma_Violent_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
