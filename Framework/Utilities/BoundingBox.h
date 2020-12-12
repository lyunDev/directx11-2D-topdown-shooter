#pragma once

struct RectEdge
{
	Vector3 LT; // left top
	Vector3 RB; // right bottom
};

struct TransformData
{
	RectEdge edge;
	Vector3 position;
	Vector3 size;
	float rotation;
};


class CollisionBuffer : public ShaderBuffer
{
public:
	CollisionBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.isOn = 1;
	}

	void SwitchRender() { data.isOn = !data.isOn; }

	struct Data
	{
		int isOn;
		Vector3 dummy;
	};
private:
	Data data;
};


class BoundingBox
{
public:
	BoundingBox(RectEdge* rect);
	~BoundingBox();

	void Init();

	void Update();
	void Render();
	function<void()> GetFuncPtr();

	//Aligned-axis Bounding box
	static bool AABB(BoundingBox* a, BoundingBox* b);
	bool CheckOutside();
private:
	RectEdge* rect;

	vector<VertexColor> vertices;
	VertexBuffer* VB = nullptr;

	vector<UINT> indices;
	IndexBuffer* IB = nullptr;

	VertexShader* VS = nullptr;
	PixelShader* PS = nullptr;

	InputLayout* IL = nullptr;

	WorldBuffer* WB = nullptr;
	Matrix world;

	Vector3 position;
	Vector3 color;

	CollisionBuffer* CB = nullptr;
	ID3D11BlendState* blend[2];
};


class OBB
{
public:
	OBB(TransformData* transform);
	~OBB();

	void Calculation();
	static bool CheckIntersect(OBB* a, OBB* b);

private:
	TransformData* transform;

	Vector3 centerW = Values::ZeroVec3;
	Vector3 centerH = Values::ZeroVec3;
	Vector3 centerPos = Values::ZeroVec3;
};