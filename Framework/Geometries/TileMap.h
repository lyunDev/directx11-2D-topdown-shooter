#pragma once

class TileMapBuffer : public ShaderBuffer
{
public :
	TileMapBuffer() : ShaderBuffer(&data, sizeof(Data))
	{

	}

	void SetMPose(Vector3 position)
	{
		data.mPos = D3DXVECTOR4(position.x, position.y, position.z, 0);
	}

	struct Data
	{
		D3DXVECTOR4 mPos;
	};
private :
	Data data;
};
class TileMap
{

public :
	TileMap(uint width, uint height, uint spacing);
	~TileMap();

	void Update();
	void Render();

	bool GetPickLocation();

	void GUI();
	void MapVertexBuffer();
	void UnmapVertexBuffer();
private :
	uint width = 0;
	uint height = 0;
	uint spacing = 0;

	uint vertexCount = 0;
	uint indexCount = 0;
	D3D11_MAPPED_SUBRESOURCE subResource;
	vector<VertexTextureColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world = Values::Identity;
	WorldBuffer* wb = nullptr;
	
	ID3D11ShaderResourceView* srv = nullptr;

	ID3D11RasterizerState* wire[2];

	Vector3 pickedLocation = Vector3(-1, -1, -1);

	TileMapBuffer* tmb = nullptr;
};