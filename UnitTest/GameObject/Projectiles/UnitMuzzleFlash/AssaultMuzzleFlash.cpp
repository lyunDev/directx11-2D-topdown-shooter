#include "stdafx.h"
#include "AssaultMuzzleFlash.h"
#include "Editor/DataGenerator.h"
AssaultMuzzleFlash::AssaultMuzzleFlash()
	: MuzzleFlash(
		Vector3(
			ASSAULT_MUZZLEFLASH_DATA.size[0], 
			ASSAULT_MUZZLEFLASH_DATA.size[1],
			ASSAULT_MUZZLEFLASH_DATA.size[2]))
{
	string path(ASSAULT_MUZZLEFLASH_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
