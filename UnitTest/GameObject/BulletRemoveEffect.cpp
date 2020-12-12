#include "stdafx.h"
#include "BulletRemoveEffect.h"
#include "Game/Transform.h"
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

BulletRemoveEffect::BulletRemoveEffect()
	: Explosion(Vector3(WinMaxWidth, WinMaxWidth, 1))
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Effect/Effect95.png");
	SetSRV(tex->GetSRV());

	Vector2 texSize = Vector2(tex->GetWidth(), tex->GetHeight());
	AnimationClip * defaultClip = new AnimationClip(L"default", tex, 4, 4, Vector2(0, 0), Vector2(texSize.x, texSize.y), 1.0f / 15.0f);
	GetAnimator()->AddAnimClip(defaultClip);
	GetAnimator()->SetCurrentAnimClip(L"default");
	
	SetActive(false);
}

BulletRemoveEffect::~BulletRemoveEffect()
{
}

