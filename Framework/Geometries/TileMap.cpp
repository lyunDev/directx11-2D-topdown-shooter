#include "Framework.h"
#include "TileMap.h"

TileMap::TileMap(uint width, uint height, uint spacing)
	:width(width), height(height), spacing(spacing)
{
	vertexCount = (width + 1) * (height + 1);
	vertices.assign(vertexCount, VertexTextureColor());
	
	int index = 0;

	for (uint y = 0; y <= height; y++)
	{
		for (uint x = 0; x <= width; x++)
		{
			vertices[index].position.x = (float)(spacing * x);
			vertices[index].position.y = (float)(spacing * y);

			vertices[index].uv.x = (float)x / (float)width;
			vertices[index].uv.y = 1 - (float)y / (float)height;
			index++;
		}
	} 
	indexCount = width * height * 6;
	indices.assign(indexCount, uint());

	index = 0;
	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			indices[index + 0] = (width + 1) * y + x;
			indices[index + 1] = (width + 1) * (y + 1) + x;
			indices[index + 2] = (width + 1) * y + x + 1;
			indices[index + 3] = (width + 1) * y + x + 1;
			indices[index + 4] = (width + 1) * (y + 1) + x;
			indices[index + 5] = (width + 1) * (y + 1) + (x + 1);

			index += 6;
		}
	}

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"VertexTextureColor.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"VertexTextureColor.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexTextureColor::descs, VertexTextureColor::count, vs->GetBlob());

	wb = new WorldBuffer();
	wb->SetWorld(world);

	Texture2D * tex = new Texture2D(TexturePath + L"AA.jpg");
	srv = tex->GetSRV();
	SAFE_DELETE(tex);

	{
		D3D11_RASTERIZER_DESC desc;
		States::GetRasterizerDesc(&desc);
		States::CreateRasterizer(&desc, &wire[0]);

		desc.FillMode = D3D11_FILL_WIREFRAME;
		States::CreateRasterizer(&desc, &wire[1]);
	}
	tmb = new TileMapBuffer();
}

TileMap::~TileMap()
{
	SAFE_RELEASE(wire[0]);
	SAFE_RELEASE(wire[1]);
	SAFE_DELETE(wb);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);
	SAFE_DELETE(ps);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void TileMap::Update()
{
	GetPickLocation();
	tmb->SetMPose(pickedLocation);
}

void TileMap::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();

	vs->SetShader();

	ps->SetShader();
	tmb->SetPSBuffer(0);
	DC->PSSetShaderResources(0, 1, &srv);
	wb->SetVSBuffer(0);
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
//	DC->RSSetState(wire[1]);
	
	DC->DrawIndexed(indexCount, 0, 0);
	//DC->RSSetState(wire[0]);
}

bool TileMap::GetPickLocation()
{
	if (vertices.size() < 1) return false;

	Vector3 mPos = Mouse::Get()->GetPosition();
	Vector3 outpos;
	Camera::Get()->UnProjection(&outpos, mPos, Values::Identity);
	outpos.z = 0.0f;
	Vector3 dir = Values::FwdVec;

	
	// u, v 는 가중치
	float u, v, distance;

	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			uint index0 = (width + 1) * y + x;
			uint index1 = (width + 1) * (y + 1) + x;
			uint index2 = (width + 1) * y + x + 1;
			uint index3 = (width + 1) * (y + 1) + (x + 1);

			Vector3 v0 = vertices[index0].position;
			Vector3 v1 = vertices[index1].position;
			Vector3 v2 = vertices[index2].position;
			Vector3 v3 = vertices[index3].position;
			
			// 가중치는 첫번째 인자로부터 얼마나 떨어졌는지
			// 정규화되어서 나옴 ex 0.2

			// 삼각형 하나
			if (D3DXIntersectTri(&v0, &v1, &v2, &outpos, &dir, &u, &v, &distance))
			{
				v0 += u * (v1 - v0) + v * (v2 - v0);
				pickedLocation = v0;
				
				if (Mouse::Get()->Down(0))
				{
					MapVertexBuffer();
					{
						vertices[index0].color = Values::Red;
						vertices[index1].color = Values::Red;
						vertices[index2].color = Values::Red;
					}
					UnmapVertexBuffer();
				}	

				return true;
			}
			// 삼각형 둘
			if (D3DXIntersectTri(&v2, &v1, &v3, &outpos, &dir, &u, &v, &distance))
			{
				v2 += u * (v1 - v2) + v * (v3 - v2);
				pickedLocation = v2;
				if (Mouse::Get()->Down(0))
				{
					MapVertexBuffer();
					{
						vertices[index2].color = Values::Red;
						vertices[index1].color = Values::Red;
						vertices[index3].color = Values::Red;
					}
					UnmapVertexBuffer();
				}
				return true;
			}
		}
	}

	return false;
}
void TileMap::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TileMap::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}
void TileMap::GUI()
{
	ImGui::Begin("Picking");
	{
		ImGui::Text(String::ToString(pickedLocation).c_str());
	}
	ImGui::End();
}
