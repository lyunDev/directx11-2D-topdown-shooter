#pragma once
#include "Geometries/TextureRect.h"

class DissolveBuffer : public ShaderBuffer
{
public :
	DissolveBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.dissolveAmount = 0.0f;
		data.fringAmount = 0.02f;
	}
	float GetDissolveAmount()
	{
		return data.dissolveAmount;
	}
	void SetDissolveAmount(float dissolveAmount)
	{
		if (dissolveAmount > 1) return;

		this->data.dissolveAmount = dissolveAmount;
	}
	void IncreaseDissolveAmount(float increaseVal)
	{
		if (this->data.dissolveAmount + increaseVal <= 1)
			this->data.dissolveAmount += increaseVal;
		else
			this->data.dissolveAmount = 1;
	}
	struct Data
	{
		float dissolveAmount; // 0 ~ 1
		float fringAmount; // 0.02 ÀûÁ¤°ª
		Vector2 padding;
	};

private :
	Data data;
};

class Dissolve : public TextureRect
{
public :
	Dissolve(Transform * transform);
	virtual ~Dissolve();

	/*void SetTexture(ID3D11ShaderResourceView * srv)
	{
		texture = srv;
	}*/
	void SetDissolveMap(ID3D11ShaderResourceView * srv)
	{
		dissolveMap = srv;
	}



	void Update();


	void Render();


protected:


//	ID3D11ShaderResourceView * texture;
	ID3D11ShaderResourceView * dissolveMap;



	DissolveBuffer * dissolveBuffer;
};