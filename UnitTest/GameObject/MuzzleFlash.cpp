//#include "stdafx.h"
//#include "MuzzleFlash.h"
//#include "Game/Transform.h"
//#include "ShaderBuffers/AlphaBuffer.h"
//#include "Utilities/Layers.h"
//
//MuzzleFlash::MuzzleFlash()
//	:GameObject(Vector3(0, 0,0 ), Vector3(100, 100, 1), 0, false)
//{
//	Texture2D * tex = new Texture2D(TexturePath + L"GameObject/MuzzleFlash.png");
//	SetSRV(tex->GetSRV());
//	SAFE_DELETE(tex);
//
//	//SetShader(ShaderPath + L"AlphaTexture.hlsl");
//
//	SetActive(false);
//	//alphaBuffer = new AlphaBuffer();
//
//	SetObjectLayer(ObjectLayer::EFFECT);
//}
//
//MuzzleFlash::~MuzzleFlash()
//{
////	SAFE_DELETE(alphaBuffer);
//}
//
//void MuzzleFlash::OnUpdate()
//{
//	if (GetAlphaBuffer()->GetAlpha() > 0 && GetActive() == true)
//	{
//		GetAlphaBuffer()->DecreaseAlpha( 10 *Time::Delta());
//	}
//	else if(GetAlphaBuffer()->GetAlpha() == 0)
//	{
//		SetActive(false);
//	}
//}
//
//void MuzzleFlash::OnRender()
//{
//	//alphaBuffer->SetPSBuffer(2);
//}
//
//void MuzzleFlash::Flash(Transform * fireTr)
//{
//	SetActive(true);
//	GetAlphaBuffer()->SetAlpha(1);
//	//transform = fireTr;
//	transform->position = fireTr.position;
//	transform->size = fireTr.size;
//	transform->rotation = fireTr.rotation;
//
//
//}
