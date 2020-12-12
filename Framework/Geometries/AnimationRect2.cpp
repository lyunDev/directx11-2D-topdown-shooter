#include "Framework.h"
#include "AnimationRect2.h"
#include "Utilities/Animator.h"
//
//AnimationRect2::AnimationRect2(Vector3 position, Vector3 size)
//	: TextureRect(position, size, 0.0f)
//{
//	SetShader(ShaderPath + L"Animation.hlsl");
//	animator = new Animator();
//	Texture2D* srcTex = new Texture2D(TexturePath + L"animationCharacter.png");
//	
//	AnimationClip* MoveDown = new AnimationClip
//	(
//		L"MoveDown",
//		srcTex,
//		5,
//		Values::ZeroVec2,
//		{ srcTex->GetWidth() * 0.5f, srcTex->GetHeight() * 0.5f }
//		, 1.0f / 15.0f
//	);
//	AnimationClip* MoveLeft = new AnimationClip
//	(
//		L"MoveLeft",
//		srcTex,
//		5,
//		Vector2(srcTex->GetWidth() * 0.5f, 0),
//		{srcTex->GetWidth(), srcTex->GetHeight() * 0.5f}
//		, 1.0f / 15.0f
//	);
//	AnimationClip * MoveUp = new AnimationClip
//	(
//		L"MoveUp",
//		srcTex,
//		5,
//		Vector2(0, srcTex->GetHeight() * 0.5f),
//		{srcTex->GetWidth() * 0.5f, srcTex->GetHeight()}
//		, 1.0f / 15.0f
//	);
//	AnimationClip * MoveRight = new AnimationClip
//	(
//		L"MoveRight",
//		srcTex,
//		5,
//		Vector2(srcTex->GetWidth() * 0.5f, srcTex->GetHeight() * 0.5f),
//		{srcTex->GetWidth(), srcTex->GetHeight()},
//		 1.0f / 15.0f,
//		true
//	);
//
//	animator->SetMoveRightClip(MoveRight);
//	animator->SetMoveLeftClip(MoveLeft);
//	animator->SetMoveUpClip(MoveUp);
//	animator->SetMoveDownClip(MoveDown);
//	//animator->AddAnimClip(RunR);
//	//animator->AddAnimClip(RunL);
//
//	//animator->SetCurrentAnimClip(L"RunL");
//	animator->PlayMoveDown();
//	SAFE_DELETE(srcTex);
//
//	{
//		D3D11_SAMPLER_DESC desc;
//		States::GetSamplerDesc(&desc);
//		States::CreateSampler(&desc, &point[0]);
//
//		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
//		States::CreateSampler(&desc, &point[1]);
//	}
//
//	{
//		D3D11_BLEND_DESC desc;
//		States::GetBlendDesc(&desc);
//		States::CreateBlend(&desc, &blend[0]);
//
//		desc.RenderTarget[0].BlendEnable = true;
//		States::CreateBlend(&desc, &blend[1]);
//	}
//}
//
//AnimationRect2::~AnimationRect2()
//{
//	SAFE_RELEASE(point[0]);
//	SAFE_RELEASE(point[1]);
//}
//
//void AnimationRect2::Update()
//{
//	animator->Update();
//
//	{
//		MapVertexBuffer();
//		{
//			vertices[0].uv =
//				Vector2
//				(
//					animator->GetCurrentFrame().x,
//					animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y
//				);
//			vertices[1].uv = animator->GetCurrentFrame();
//			vertices[2].uv = animator->GetCurrentFrame() + animator->GetTexelFrameSize();
//			vertices[3].uv =
//				Vector2
//				(
//					animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x,
//					animator->GetCurrentFrame().y
//				);
//
//
//		}
//		UnmapVertexBuffer();
//
//		// update world
//		UpdateWorld();
//	}
//	Move();
//}
//
//void AnimationRect2::Render()
//{
//
//	SetSRV(animator->GetCurrentSRV());
//	DC->PSSetSamplers(0, 1, &point[1]); // sampler point
//	DC->OMSetBlendState(blend[1], nullptr, 0xffffffff);
//	TextureRect::Render();
//	DC->OMSetBlendState(blend[0], nullptr, 0xffffffff);
//	DC->PSSetSamplers(0, 1, &point[0]); // sampler linear
//	// __super::render();
//
//}
//
//void AnimationRect2::Move()
//{
//	if (Keyboard::Get()->Press('A'))
//	{
//		position.x -= 100 * Time::Delta();
//		//animator->SetCurrentAnimClip(L"RunL");
//		animator->PlayMoveLeft();
//	}
//	else if (Keyboard::Get()->Press('D'))
//	{
//		position.x += 100 * Time::Delta();
//		//animator->SetCurrentAnimClip(L"RunR");
//		animator->PlayMoveRight();
//	}
//	else if (Keyboard::Get()->Press('W'))
//	{
//		position.y += 100 * Time::Delta();
//		//animator->SetCurrentAnimClip(L"RunR");
//		animator->PlayMoveUp();
//	}
//	else if (Keyboard::Get()->Press('S'))
//	{
//		position.y -= 100 * Time::Delta();
//		//animator->SetCurrentAnimClip(L"RunR");
//		animator->PlayMoveDown();
//	}
//}
