#include "Framework.h"
#include "TextureFilterRect.h"


TextureFilterRect::TextureFilterRect(wstring path, Vector3 position, Vector3 size, float rotation)
	: position(position), size(size), rotation(rotation)
{

	//vertices

	{

		vertices.assign(4, VertexTexture());



		vertices[0].position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);

		vertices[0].uv = Vector2(0, 1);



		vertices[1].position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

		vertices[1].uv = Vector2(1, 0);



		vertices[2].position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);

		vertices[2].uv = Vector2(1, 1);



		vertices[3].position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);

		vertices[3].uv = Vector2(0, 0);
	}



	//vertexBuffer

	{
		vb = new VertexBuffer();

		vb->Create(vertices, D3D11_USAGE_DYNAMIC);
	}



	//indexBuffer

	{

		indices = { 0, 1, 2, 0, 3, 1 };



		ib = new IndexBuffer();

		ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	}



	//vertexShader

	{

		vs = new VertexShader();

		vs->Create(ShaderPath + L"TextureFilter.hlsl", "VS");
	}



	//inputLayout

	{

		il = new InputLayout();

		il->Create(VertexTexture::descs, VertexTexture::count, vs->GetBlob());

	}



	//pixelShader

	{

		ps = new PixelShader();

		ps->Create(ShaderPath + L"TextureFilter.hlsl", "PS");

	}
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	blendDesc.IndependentBlendEnable = false;

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	HRESULT hr = DEVICE->CreateBlendState(&blendDesc, &blendState);
	CHECK(hr);

	wb = new WorldBuffer();
	filterBuffer = new FilterBuffer();

	hr = D3DX11CreateShaderResourceViewFromFile
	(
		DEVICE,
		path.c_str(),
		nullptr,
		nullptr,
		&srv,
		nullptr
	);
	CHECK(hr);


}



TextureFilterRect::~TextureFilterRect()

{

	SAFE_DELETE(wb);



	SAFE_DELETE(ps);



	SAFE_DELETE(il);



	SAFE_DELETE(vs);



	SAFE_DELETE(ib);

	SAFE_DELETE(vb);

}


void TextureFilterRect::SetFilter(FilterType filterType)
{
	filterBuffer->SetFilterType(filterType);
}
void TextureFilterRect::Update()

{
	/*if (Keyboard::Get()->Press('W'))

	position.y += 10;

	else if (Keyboard::Get()->Press('S'))

	position.y -= 10;

	​

	if (Keyboard::Get()->Press('A'))

	position.x -= 10;

	else if (Keyboard::Get()->Press('D'))

	position.x += 10;*/

	D3DXMatrixTranslation(&T, position.x, position.y, position.z);
	D3DXMatrixScaling(&S, size.x, size.y, size.z);
	//D3DXMatrixRotationZ(&R, (float)D3DXToRadian(rotation));
	D3DXMatrixRotationZ(&R, rotation);

	world = S * R* T;

	wb->SetWorld(world);
}



void TextureFilterRect::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();

	wb->SetVSBuffer(0); // set constant buffer (transform buffer)
	filterBuffer->SetPSBuffer(2);
	ps->SetShader();
	DC->PSSetShaderResources(0, 1, &srv);

	//	DC->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
	DC->DrawIndexed(ib->GetCount(), 0, 0);

}

void TextureFilterRect::GUI()
{

	static int filterType = 0;

	ImGui::RadioButton("Grayscale", &filterType, 0);
	ImGui::RadioButton("Sepia", &filterType, 1);
	SetFilter((FilterType)filterType);
}

void TextureFilterRect::UpdateColor()
{
	/*D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		for (VertexTexture& v : vertices)
		{
			v.color = this->color;
		}
		memcpy(subResource.pData, vertices.data(), vb->GetCount() * vb->GetStride());
	}
	DC->Unmap(vb->GetResource(), 0);*/
}

string TextureFilterRect::MakeLabel(string preFix)
{
	string label = preFix + "##" + to_string((uint)this);
	return label;
}
