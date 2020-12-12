#pragma once


class Rect
{
public :
	Rect(Vector3 position, Vector3 size, float rotation);
	~Rect();

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

	//BoundingBox * GetBox() { return box; }
	//bool static AABB(BoundingBox * other, BoundingBox * box2)
	//{
	//	return BoundingBox::AABB(other, box2);
	//}

	Vector3 GetPosition() { return position; }
	void SetPosition(Vector3 position) { this->position = position; }

	void SyncTransform(Vector3 position, Vector3 size, float rotation)
	{
		this->position = position;
		this->size = size;
		this->rotation = rotation;
	}

private :
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

	//RectEdge edge ;
	//BoundingBox * box = nullptr;
};