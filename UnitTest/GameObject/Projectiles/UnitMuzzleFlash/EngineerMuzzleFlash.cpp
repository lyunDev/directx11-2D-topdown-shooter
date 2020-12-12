#include "stdafx.h"
#include "EngineerMuzzleFlash.h"
#include "Editor/DataGenerator.h"
EngineerMuzzleFlash::EngineerMuzzleFlash()
	: MuzzleFlash(
		Vector3(
			ENGINEER_MUZZLEFLASH_DATA.size[0],
			ENGINEER_MUZZLEFLASH_DATA.size[1],
			ENGINEER_MUZZLEFLASH_DATA.size[2]))
{
	string path(ENGINEER_MUZZLEFLASH_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}

