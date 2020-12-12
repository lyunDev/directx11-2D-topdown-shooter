#pragma once

class TextureFilterRect
{
public:
	TextureFilterRect(wstring path, Vector3 position, Vector3 size, float rotation);
	~TextureFilterRect();

	void Update();
	void Render();

	void GUI();

	void UpdateColor();
	string MakeLabel(string preFix);

	void SetFilter(FilterType filterType);

private:
	vector<VertexTexture> vertices;
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
	FilterBuffer * filterBuffer = nullptr;
	bool bOpen = true;

	ID3D11BlendState *blendState = nullptr;

	ID3D11ShaderResourceView * srv;


};