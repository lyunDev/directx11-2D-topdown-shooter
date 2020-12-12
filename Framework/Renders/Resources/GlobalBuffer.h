#pragma once
#include "Framework.h"


enum class FilterType {Grayscale = 0, Sepia};
class FilterBuffer : public ShaderBuffer
{
public :
	FilterBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		data.filterType = 0;
	}
	void SetFilterType(FilterType type)
	{
		data.filterType = (uint)type;
	}
	struct Data
	{
		uint filterType;
		uint padding[3];
	};
private:
	Data data;
};
class WorldBuffer : public ShaderBuffer
{
public :
	WorldBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.world);
	}

	void SetWorld(D3DXMATRIX world)
	{
		D3DXMatrixTranspose(&data.world, &world);

	}

	struct Data
	{
		D3DXMATRIX world;
	};
private :
	Data data;

};

class VPBuffer : public ShaderBuffer
{
public :
	VPBuffer() : ShaderBuffer(&data, sizeof(Data))
	{
		D3DXMatrixIdentity(&data.view);
		D3DXMatrixIdentity(&data.projection);
	}
	void SetView(D3DXMATRIX view)
	{
		D3DXMatrixTranspose(&data.view, &view);
	}
	void SetProj(D3DXMATRIX projection)
	{
		D3DXMatrixTranspose(&data.projection, &projection);
	}
	struct Data
	{
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};
private :
	Data data;
};