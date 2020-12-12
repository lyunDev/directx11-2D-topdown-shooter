#pragma once

#include "Framework.h"

class AlphaBuffer : public ShaderBuffer
{
public :
	AlphaBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.alpha = 1;
	}
	void SetAlpha(float alpha)
	{
		if (alpha > 1 || alpha < 0)
			return;
		data.alpha = alpha;
	}
	void DecreaseAlpha(float decrease)
	{
		if (data.alpha - decrease >= 0)
		{
			data.alpha -= decrease;
		}
		else
			data.alpha = 0;
	}
	void IncreaseAlpha(float increase)
	{
		if (data.alpha + increase >= 1)
			data.alpha = 1;
		else
			data.alpha += increase;
	}

	float GetAlpha()
	{
		return data.alpha;
	}
	struct Data
	{
		float alpha;
		Vector3 padding;
	};

private :
	Data data;
};