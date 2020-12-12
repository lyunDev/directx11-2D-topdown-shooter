#pragma once


class OBBRect
{
public:
	OBBRect(Vector3 position, Vector3 size, float rotation);
	~OBBRect();

	void Update();
	void Render();

	void GUI();

	void Move();

	void UpdateColor();
	string MakeLabel(string preFix);

	void UpdateWorld();

	void SetColor(Color color)
	{
		this->color = color;
		UpdateColor();
	}


	OBB * GetOBB() { return obb; }

private:
	vector<VertexColor> vertices;
	VertexBuffer* vb = nullptr;

	vector<UINT> indices;
	IndexBuffer * ib = nullptr;

	VertexShader* vs = nullptr;
	PixelShader* ps = nullptr;
	ID3DBlob* vsBlob = nullptr;

	InputLayout* il = nullptr;
	ID3DBlob* psBlob = nullptr;

	D3DXMATRIX world;
	D3DXMATRIX S, R, T;

	D3DXVECTOR3 position;
	D3DXVECTOR3 size;
	float rotation;

	Color color = Color(1, 0, 0, 1);

	WorldBuffer * wb = nullptr;

	bool bOpen = true;

	ID3D11BlendState *blendState[2];

	RectEdge * edge = nullptr;
	//BoundingBox * box = nullptr;

	OBB* obb = nullptr;
	TransformData transform;
};