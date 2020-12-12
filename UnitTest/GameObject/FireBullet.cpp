#include "stdafx.h"
#include "FireBullet.h"
#include "Game/Transform.h"
#include "Geometries/AnimationRect.h"
#include "Utilities/Animator.h"

FireBullet::FireBullet()
	: GameObject(Vector3(0, 0, 0), Vector3(100, 100, 1), 0, true)
{
	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/Explosion03.png");
	SetSRV(tex->GetSRV());
	
	Vector2 texSize = Vector2(tex->GetWidth(), tex->GetHeight());
	AnimationClip * idle = new AnimationClip(L"Idle", tex, 4, 4, Vector2(0, 0), Vector2(texSize.x, texSize.y), 1.0f / 15.0f);
	GetAnimator()->AddAnimClip(idle);
	GetAnimator()->SetCurrentAnimClip(L"Idle");
//	SAFE_DELETE(tex);

	GetAnimator()->onAnimationFinished = [&]()->void {GetAnimator()->AnimStop(); };


	SetActive(true);
	SetTag("Bullet");
	SetRenderLayer(RenderLayer::PROJECTILE);

}



void FireBullet::OnUpdate()
{
}

void FireBullet::Fire(Transform fireTr)
{
}
