#include "stdafx.h"
#include "WideExplosion.h"
#include "Game/Transform.h"
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

WideExplosion::WideExplosion()
	: Explosion(Vector3(WinMaxWidth - 300, WinMaxWidth - 300, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Effect/effect02.png");
	SetSRV(tex->GetSRV());

	Vector2 texSize = Vector2(tex->GetWidth(), tex->GetHeight());
	AnimationClip * defaultClip = new AnimationClip(L"default", tex, 5, 2, Vector2(0, 0), Vector2(texSize.x, texSize.y), 1.0f / 15.0f);
	GetAnimator()->AddAnimClip(defaultClip);
	GetAnimator()->SetCurrentAnimClip(L"default");

	SetActive(false);
}

WideExplosion::~WideExplosion()
{
}
