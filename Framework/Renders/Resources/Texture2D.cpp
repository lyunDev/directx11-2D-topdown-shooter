#include "Framework.h"
#include "Texture2D.h"

using namespace DirectX;

vector<TextureDesc> Textures::descs;

Texture2D::Texture2D(wstring filePath)
	: filePath(filePath)
{
	Textures::Load(this);
}
void Texture2D::ReadPixel(vector<Color>* pixels)
{
	ID3D11Texture2D* texture;
	srv->GetResource((ID3D11Resource**)&texture);

	ReadPixel(texture, pixels);
}

void Texture2D::ReadPixel(ID3D11Texture2D * texture, vector<Color>* pixels)
{
	D3D11_TEXTURE2D_DESC srcDesc;
	texture->GetDesc(&srcDesc);

	D3D11_TEXTURE2D_DESC destDesc;
	ZERO(destDesc);
	int a = sizeof(D3D11_TEXTURE2D_DESC);
	int b = sizeof(D3D11_TEXTURE1D_DESC);
	int c = sizeof(srcDesc);
	//memcpy(&destDesc, &srcDesc, sizeof(D3D11_TEXTURE2D_DESC));
	destDesc.Usage = D3D11_USAGE_STAGING;
	destDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	destDesc.Width = srcDesc.Width;
	destDesc.Height = srcDesc.Height;
	destDesc.MipLevels = 1;
	destDesc.ArraySize = 1;
	destDesc.Format = srcDesc.Format;
	destDesc.SampleDesc = srcDesc.SampleDesc;

	ID3D11Texture2D* destTex = nullptr;
	HRESULT hr = DEVICE->CreateTexture2D(&destDesc, nullptr, &destTex);
	CHECK(hr);

	D3DX11LoadTextureFromTexture(DC, texture, nullptr, destTex);

	uint* colors = new uint[destDesc.Width * destDesc.Height];
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(destTex, 0, D3D11_MAP_READ, 0, &subResource);
	{
		memcpy(colors, subResource.pData, sizeof(uint) * destDesc.Width * destDesc.Height);
	}
	DC->Unmap(destTex, 0);
	char* colorMem = (char*)colors;
	for (int i = 0; i < destDesc.Width * destDesc.Height; i++)
	{
		int offset = (i * sizeof(uint));
		char temp = colorMem[offset];
		colorMem[offset] = colorMem[offset + 2];
		colorMem[offset + 2] = temp;
		/*char r = *(colorMem + i / sizeof(uint));
		char b = *(colorMem + i / sizeof(uint) + 2);

		*(colors + i) = b;
		*(colors + i + 2) = r;*/
	}





	pixels->assign(&colors[0], &colors[(destDesc.Width * destDesc.Height) - 1]);

	SAFE_DELETE_ARRAY(colors);
	SAFE_RELEASE(destTex);
}

void Textures::Delete()
{
	for (TextureDesc desc : descs)
		SAFE_RELEASE(desc.srv);
}

unordered_map<wstring, Texture2D> Textures::textureMap;

void Textures::Load(Texture2D * texture)
{
	auto find = textureMap.find(texture->filePath);
	if (find != textureMap.end()) // 이미 있으면
	{
		texture->srv = (*find).second.srv;
		texture->metaData = (*find).second.metaData;
		return;
	}
	HRESULT hr;
	TexMetadata metaData;
	// png, jpg, bmp => wic 

	wstring ext = Path::GetExtension(texture->filePath);
	if (ext == L"tga")
	{
		hr = GetMetadataFromTGAFile(texture->filePath.c_str(), metaData);
		CHECK(hr);
	}
	else if (ext == L"dds")
	{
		hr = GetMetadataFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, metaData);
		CHECK(hr);
	}
	else
	{
		hr = GetMetadataFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, metaData);
		if (!SUCCEEDED(hr))
		{
			int a = 0;
		}
		CHECK(hr);
		/*
			여기서 에러 나오면 경로문제
		*/
	}

	uint width = metaData.width;
	uint height = metaData.height;

	TextureDesc desc;
	desc.filePath = texture->filePath;
	desc.width = width;
	desc.height = height;

	TextureDesc exist;
	bool bExist = false;
	for (TextureDesc temp : descs)
	{
		if (desc == temp)
		{
			bExist = true;
			exist = temp;

			break;
		}
	}

	if (bExist == true)
	{
		texture->srv = exist.srv;
	}
	else
	{
		ScratchImage image;

		if (ext == L"tga")
		{
			hr = LoadFromTGAFile(texture->filePath.c_str(), &metaData, image);
			CHECK(hr);
		}
		else if (ext == L"dds")
		{
			hr = LoadFromDDSFile(texture->filePath.c_str(), DDS_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}
		else // wic
		{
			hr = LoadFromWICFile(texture->filePath.c_str(), WIC_FLAGS_NONE, &metaData, image);
			CHECK(hr);
		}

		ID3D11ShaderResourceView * srv = nullptr;
		hr = CreateShaderResourceView
		(
			DEVICE,
			image.GetImages(),
			image.GetImageCount(),
			metaData,
			&srv
		);
		CHECK(hr);

		desc.srv = srv;
		texture->srv = srv;
		texture->metaData = metaData;

		descs.push_back(desc);
	}
	textureMap.insert(make_pair(texture->filePath, *texture));
}