#include "stdafx.h"
#include "NebulizerMuzzleFlash.h"
#include "Editor/DataGenerator.h"
NebulizerMuzzleFlash::NebulizerMuzzleFlash()
	: MuzzleFlash(
		Vector3(
			NEBULIZER_MUZZLEFLASH_DATA.size[0],
			NEBULIZER_MUZZLEFLASH_DATA.size[1],
			NEBULIZER_MUZZLEFLASH_DATA.size[2]))
{
	string path(NEBULIZER_MUZZLEFLASH_DATA.texturePath);
	Texture2D * tex = new Texture2D(String::ToWstring(path));
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}
