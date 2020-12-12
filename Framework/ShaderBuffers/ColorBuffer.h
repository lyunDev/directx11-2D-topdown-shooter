#pragma once

#include "Framework.h"



class ColorBuffer :public ShaderBuffer
{

public :
	ColorBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.color = Color(0, 0, 0, 0);
	}
	void SetColor(Color color)
	{
		data.color = color;
	}
	Color GetColor()
	{
		return data.color;
	}
	struct Data
	{
		Color color;
	};

private :
	Data data;
};