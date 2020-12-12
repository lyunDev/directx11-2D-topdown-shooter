#pragma once

#include "Framework.h"



class UIElementBuffer :public ShaderBuffer
{

public:
	UIElementBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.addColor = Color(0, 0, 0, 0);
		data.processAmount = 1.0f;
	}
	void SetAddColor(Color addColor)
	{
		data.addColor = addColor;
	}
	Color  GetAddColor()
	{
		return data.addColor;
	}
	void SetProcessAmount(float processAmount)
	{
		data.processAmount = processAmount;
	}
	float GetProcessAmount()
	{
		return data.processAmount;
	}
	struct Data
	{
		Color addColor;
		float processAmount;
		Vector3 padding;
	};

private:
	Data data;
};