#include "stdafx.h"
#include "CloneMuzzleFlash.h"
#include "Editor/DataGenerator.h"
CloneMuzzleFlash::CloneMuzzleFlash()
	: MuzzleFlash(
		Vector3(
			CLONE_MUZZLEFLASH_DATA.size[0],
			CLONE_MUZZLEFLASH_DATA.size[1],
			CLONE_MUZZLEFLASH_DATA.size[2]))
{
	string path(CLONE_MUZZLEFLASH_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
