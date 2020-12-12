#pragma once

struct  VertexColor
{
	VertexColor() : position(0, 0, 0), color(0, 0, 0, 0) {}
	VertexColor(Vector3 position, Color color)
		: position(position), color(color) {}
	Vector3 position;
	Color color;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;
};
struct VertexTexture
{
	VertexTexture() : position(0, 0, 0), uv(0, 0) {};
	VertexTexture(Vector3 position, Vector2 uv)
		: position(position), uv(uv) {}
	Vector3 position;
	Vector2 uv;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;
	//TEXTCORD 
};

struct VertexTextureColor
{
	VertexTextureColor() : position(0, 0, 0), uv(0, 0), color(0, 0, 0, 0) {};
	VertexTextureColor(Vector3 position, Vector2 uv, Color color)
		: position(position), uv(uv), color(color){}
	Vector3 position;
	Vector2 uv;
	Color color;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 3;
	//TEXTCORD 
};

struct VertexTile
{
	VertexTile() : position(0, 0, 0), uv(0, 0), color(0, 0, 0, 0), uv2(0, 0), index(0), bWalkable(true) {};
	VertexTile(Vector3 position, Vector2 uv,Vector2 uv2, uint index, Color color, bool bWalkable = true)
		: position(position), uv(uv), color(color), bWalkable(true), uv2(uv2), index(index) {}
	Vector3 position;
	Vector2 uv;
	Vector2 uv2;	
	Color color;
	uint index;
	bool bWalkable;
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 6;
	//TEXTCORD 
};