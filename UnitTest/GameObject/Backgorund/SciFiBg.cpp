#include "stdafx.h"
#include "SciFiBg.h"

SciFiBg::SciFiBg()
{
	Texture2D *tex = new Texture2D(TexturePath + L"GameObject/Background/Sci_fi_background.png");
	SetSRV(tex->GetSRV());
	SAFE_DELETE(tex);
}

SciFiBg::~SciFiBg()
{
}
