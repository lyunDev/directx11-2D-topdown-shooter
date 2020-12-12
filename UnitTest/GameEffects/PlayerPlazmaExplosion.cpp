#include "stdafx.h"
#include "PlayerPlazmaExplosion.h"
#include "Game/Transform.h"
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

PlayerPlazmaExplosion::PlayerPlazmaExplosion()
	: Explosion(Vector3(300, 300, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Effect/Effect97.png");
	SetSRV(tex->GetSRV());

	Vector2 texSize = Vector2(tex->GetWidth(), tex->GetHeight());
	AnimationClip * defaultClip = new AnimationClip(L"default", tex, 4, 4, Vector2(0, 0), Vector2(texSize.x, texSize.y), 1.0f / 15.0f);
	GetAnimator()->AddAnimClip(defaultClip);
	GetAnimator()->SetCurrentAnimClip(L"default");

	SetActive(false);
}

PlayerPlazmaExplosion::~PlayerPlazmaExplosion()
{
}
