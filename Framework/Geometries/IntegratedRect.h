#pragma once
#include "Game/GameObject.h"

class Transform;
class IntegratedRect
{
	friend GameObject;
public:
	IntegratedRect(Transform * transform);
	virtual ~IntegratedRect();


	void SetSRV(ID3D11ShaderResourceView* srv)
	{
		//SAFE_RELEASE(this->srv);
		this->srv = srv;
	}

	void SetShader(wstring shaderPath);


	void Update();

	void UpdateWorld();

	void Render();

	string MakeLabel(string preFix);

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	/*void SyncTransform(Vector3 position, Vector3 size, float rotation)
	{
		this->position = position;
		this->size = size;
		this->rotation = rotation;
	}*/
protected:
	vector<VertexTexture> vertices;
	VertexBuffer* vb = nullptr;
	D3D11_MAPPED_SUBRESOURCE subResource;


	vector<UINT> indices;
	IndexBuffer * ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;
	ID3DBlob* vsBlob = nullptr;

	InputLayout* il = nullptr;
	ID3DBlob* psBlob = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX S, R, T;

	/*D3DXVECTOR3 position;
	D3DXVECTOR3 size;
	float rotation;*/
	class Transform * transform;

	Color color = Color(1, 0, 0, 1);

	WorldBuffer * wb = nullptr;

	bool bOpen = true;

	ID3D11BlendState *blendState = nullptr;

	ID3D11ShaderResourceView * srv;
	ID3D11ShaderResourceView * dissolveMap;

	RectEdge * edge = nullptr;
	BoundingBox * box = nullptr;

	class AlphaBuffer * alphaBuffer;
	class ColorBuffer * colorBuffer;
	class DissolveBuffer * dissolveBuffer;
};