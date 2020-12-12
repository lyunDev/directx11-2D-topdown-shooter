//#pragma once
//
//
//class ShadedBuffer : public ShaderBuffer
//{
//public :
//	ShadedBuffer() : ShaderBuffer(&data, sizeof(Data))
//	{
//		data.selection = 1;
//	}
//	int* GetSelectionPtr() { return &data.selection; }
//	struct Data
//	{
//		int selection;
//		Vector3 dummy;
//	};
//
//private :
//	Data data;
//};
//
//#include "TextureRect.h"
//class ShadedTexture : public TextureRect
//{
//public :
//	ShadedTexture(wstring path, Vector3 position, Vector3 size, float rotation);
//	~ShadedTexture();
//
//	void Render();
//
//	void GUI();
//
//private :
//
//	ShadedBuffer* sb = nullptr;
//
//};