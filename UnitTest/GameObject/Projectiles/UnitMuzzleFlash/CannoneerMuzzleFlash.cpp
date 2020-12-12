#include "stdafx.h"
#include "CannoneerMuzzleFlash.h"
#include "Editor/DataGenerator.h"
CannoneerMuzzleFlash::CannoneerMuzzleFlash()
	: MuzzleFlash(
		Vector3(
			CANNONEER_MUZZLEFLASH_DATA.size[0],
			CANNONEER_MUZZLEFLASH_DATA.size[1],
			CANNONEER_MUZZLEFLASH_DATA.size[2]))
{
	string path(CANNONEER_MUZZLEFLASH_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}