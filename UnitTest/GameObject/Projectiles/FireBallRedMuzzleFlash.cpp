#include "stdafx.h"
#include "FireBallRedMuzzleFlash.h"

FireBallRedMuzzleFlash::FireBallRedMuzzleFlash()
	: MuzzleFlash(Vector3(100, 200, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Projectiles/FireBall_Orange_Splash.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}