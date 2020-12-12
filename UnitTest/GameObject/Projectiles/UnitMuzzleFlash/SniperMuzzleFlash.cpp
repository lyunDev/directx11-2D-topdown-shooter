#include "stdafx.h"
#include "SniperMuzzleFlash.h"
#include "Editor/DataGenerator.h"
SniperMuzzleFlash::SniperMuzzleFlash()
	: MuzzleFlash(
		Vector3(
			SNIPER_MUZZLEFLASH_DATA.size[0],
			SNIPER_MUZZLEFLASH_DATA.size[1],
			SNIPER_MUZZLEFLASH_DATA.size[2]))
{
	string path(SNIPER_MUZZLEFLASH_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
