#pragma once


class InputLayout
{
public :
	~InputLayout();

	void Create(D3D11_INPUT_ELEMENT_DESC* desc, uint count, ID3DBlob* blob);
	void SetIA();
private :
	ID3D11InputLayout* inputLayout = nullptr;
};