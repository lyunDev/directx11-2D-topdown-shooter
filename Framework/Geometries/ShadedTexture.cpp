#include "Framework.h"
#include "TextureRect.h"
#include "ShadedTexture.h"
//
//ShadedTexture::ShadedTexture(wstring path, Vector3 position, Vector3 size, float rotation) 
//	: TextureRect(path, position, size, rotation)
//{
//	sb = new ShadedBuffer();
//}
//
//ShadedTexture::~ShadedTexture()
//{
//	SAFE_DELETE(sb);
//}
//
//void ShadedTexture::Render()
//{
//	TextureRect::Render();
//	// __super::Render();
//	sb->SetPSBuffer(0);
//}
//
//
//
//void ShadedTexture::GUI()
//{
//	ImGui::Begin("Shaded");
//	{
//		ImGui::RadioButton("AM", sb->GetSelectionPtr(), 1);
//		ImGui::RadioButton("FM", sb->GetSelectionPtr(), 2);
//		ImGui::RadioButton("Sepia", sb->GetSelectionPtr(), 3);
//	}
//	ImGui::End();
//}
