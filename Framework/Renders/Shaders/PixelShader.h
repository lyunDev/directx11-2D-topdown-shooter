#pragma once
#include "IShader.h"

class PixelShader : public IShader
{
public :
	// IShader을(를) 통해 상속됨
	virtual void Create(const wstring path, const string entryName) override;
	virtual void Clear() override;
	virtual void SetShader() override;

	ID3DBlob* GetBlob() { return blob; }
	ID3D11PixelShader* GetResource() { return shader; }

private :
	ID3D11PixelShader * shader = nullptr;
	ID3DBlob* blob = nullptr;
};
