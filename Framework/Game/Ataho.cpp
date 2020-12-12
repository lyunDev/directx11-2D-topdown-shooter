#include "Framework.h"
#include "Ataho.h" 
//
//Ataho::Ataho(Vector3 position, Vector3 size)
//	: Character(position, size)
//{
//	
//	Texture2D* srcTex = new Texture2D(TexturePath + L"ataho3.png");
//	Vector2 texSize = Vector2(srcTex->GetWidth(), srcTex->GetHeight());
//	AnimationClip* runD = new AnimationClip(L"RunD", srcTex, 5, Vector2(0, 0), texSize * 0.5f, 1.0f / 15.0f);
//	AnimationClip* runL = new AnimationClip(L"RunL", srcTex, 5, Vector2(texSize.x * 0.5f, 0), Vector2(texSize.x, texSize.y * 0.5f), 1.0f / 15.0f);
//	AnimationClip* runU = new AnimationClip(L"RunU", srcTex, 5, Vector2(0, texSize.y * 0.5f), Vector2(texSize.x * 0.5f, texSize.y), 1.0f / 15.0f);
//	AnimationClip* runR = new AnimationClip(L"RunR", srcTex, 5, texSize * 0.5f, texSize, 1.0f / 15.0f);
//
//	Texture2D* attackTex = new Texture2D(TexturePath + L"attack.png");
//	texSize = Vector2(attackTex->GetWidth(), attackTex->GetHeight());
//	AnimationClip * attack = new AnimationClip(L"Attack", attackTex, 4, Values::ZeroVec2, texSize, 1.0f / 10.0f);
//
//	animator->SetMoveDownClip(runD);
//	animator->SetMoveUpClip(runU);
//	animator->SetMoveLeftClip(runL);
//	animator->SetMoveRightClip(runR);
//	animator->SetActionClip(attack);
//
//	
//	animator->PlayMoveDown();
//
//	animRect->SetAnimator(animator);
//
//	SAFE_DELETE(srcTex);
//	SAFE_DELETE(attackTex);
//
//	// 유한상태기계 FSM
//	// 행동트리 Behaviour Tree
//}
//
//Ataho::~Ataho()
//{
//}
//
//void Ataho::Update()
//{
//	animRect->Update();
//	animator->Update();
//
//}
//
//void Ataho::Render()
//{
//	animRect->Render();
//}
