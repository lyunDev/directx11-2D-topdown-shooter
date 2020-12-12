#pragma once

#include "Framework.h"



class ProgressBuffer :public ShaderBuffer
{

public:
	ProgressBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.processAmount = 1.0f;
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
		float processAmount;
		Vector3 padding;
	};

private:
	Data data;
};