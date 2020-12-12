#pragma once

class TileSet : public SingletonBase<TileSet>
{
public :
	friend class SingletonBase<TileSet>;
	friend class TMap;


	void GUI();
	ID3D11ShaderResourceView* GetSRV() { return tileSRV; }

private :
	TileSet();
	~TileSet();

private : 
	ID3D11ShaderResourceView * tileSRV = nullptr;

	uint tileXCount = 0;
	uint tileYCount = 0;

	Vector2 selectedStartUV = Values::ZeroVec2;
	Vector2 texelTileSize = Values::ZeroVec2;


};