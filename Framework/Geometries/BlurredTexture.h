//#pragma once
//
//#include "TextureRect.h"
//
//
//class BlurBuffer : public ShaderBuffer
//{
//public :
//	BlurBuffer() : ShaderBuffer(&data, sizeof(Data))
//	{
//		data.textureSize = Values::ZeroVec2;
//		data.blurCount = 1;
//	}
//
//	void SetTextureSize(Vector2 size)
//	{
//		data.textureSize = size;
//	}
//	int *GetBlurCountPtr() { return &data.blurCount; }
//	struct Data
//	{
//		Vector2 textureSize;
//		int blurCount;
//		int dummy;
//	};
//private :
//	Data data;
//};
//
//class BlurredTexture : public TextureRect
//{
//public : 
//	BlurredTexture(wstring path, Vector3 position, Vector3 size, float rotation);
//	~BlurredTexture();
//
//	void Update();
//	void Render();
//	void GUI();
//private :
//	BlurBuffer * buffer = nullptr;
//};