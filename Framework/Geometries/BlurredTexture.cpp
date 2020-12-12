#include "Framework.h"
#include "BlurredTexture.h"
//
//BlurredTexture::BlurredTexture(wstring path, Vector3 position, Vector3 size, float rotation)
//	: TextureRect(path, position, size, rotation)
//{
//	buffer = new BlurBuffer();
//	buffer->SetTextureSize({size.x, size.y});
//}
//
//BlurredTexture::~BlurredTexture()
//{
//	SAFE_DELETE(buffer);
//}
//
//void BlurredTexture::Update()
//{
//	TextureRect::Update();
//}
//
//void BlurredTexture::Render()
//{
//	buffer->SetPSBuffer(0);
//	TextureRect::Render();
//	
//}
//
//void BlurredTexture::GUI()
//{
//	ImGui::Begin("Blur");
//	{
//		ImGui::SliderInt("BlurCount", buffer->GetBlurCountPtr(), 1, 10);
//	}
//	ImGui::End();
//}
