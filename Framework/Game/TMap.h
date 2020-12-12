#pragma once

enum EDrawingMode
{
	Normal,
	Redcell,
};

class TileBuffer : public ShaderBuffer
{
public :
	TileBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
	}
	void SetTileIndex(uint index) { data.tileIndex = index; }
	struct Data
	{
		uint tileIndex = -1;
		Vector3 padding;
	};
private :
	Data data;
};

class TMap
{
public :
	TMap(uint width, uint height, uint spacing);
	~TMap();

	void Update();
	void Render();

	void GenerateTileMap();

	void MapVertexBuffer();
	void UnmapVertexBuffer();

	void GUI();

	Tile* GetTile(Vector3 mPos);

	void Save();
	void Load();

	void Build();
	void FindPath(Tile* start, Tile * end);

	void SaveTileInfos();
private :
	uint width = 0;
	uint height = 0;
	uint spacing = 0;

	uint vertexCount = 0;
	uint indexCount = 0;
	D3D11_MAPPED_SUBRESOURCE subResource;
	vector<VertexTile> vertices;
	VertexBuffer* vb = nullptr;

	vector<uint> indices;
	IndexBuffer* ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;

	InputLayout* il = nullptr;

	Matrix world = Values::Identity;
	WorldBuffer* wb = nullptr;

	class Tile** tiles = nullptr;

	EDrawingMode mode = Normal;

	TileBuffer* tb = nullptr;
};

