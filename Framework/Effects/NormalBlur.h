#pragma once

#include "Geometries/TextureRect.h"

class BlurBuffer : public ShaderBuffer
{
public:
	BlurBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.textureSize = Values::ZeroVec2;
		data.blurCount = 1;
	}

	void SetTextureSize(Vector2 size)
	{
		data.textureSize = size;
	}
	void SetBlurCount(int blurCount)
	{
		data.blurCount = blurCount;
	}
	struct Data
	{
		Vector2 textureSize;
		int blurCount; // 적정값 : 1 ~ 5 (1 : 기본값)
		int dummy;
	};
private:
	Data data;
};

class NormalBlur : public TextureRect
{
public:
	NormalBlur(Transform * transform);
	~NormalBlur();

	void SetBlurCount(int blurCount)
	{
		buffer->SetBlurCount(blurCount);
	}
	void Update();
	void Render();

private:
	BlurBuffer * buffer = nullptr;
};