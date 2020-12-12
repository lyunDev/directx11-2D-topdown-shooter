#include "Framework.h"
#include "InputLayout.h"

InputLayout::~InputLayout()
{
	SAFE_RELEASE(inputLayout);
}

void InputLayout::Create(D3D11_INPUT_ELEMENT_DESC * desc, uint count, ID3DBlob * blob)
{
	if (!desc || !count || !blob)
		CHECK(false);

	HRESULT hr = DEVICE->CreateInputLayout
	(
		desc,
		count,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout
	);
	CHECK(hr);
}

void InputLayout::SetIA()
{
	DC->IASetInputLayout(inputLayout);
}
