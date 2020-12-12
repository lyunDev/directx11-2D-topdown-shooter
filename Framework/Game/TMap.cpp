#include "Framework.h"
#include "TMap.h"
#include "TileSet.h"
#include "Tile.h"

TMap::TMap(uint width, uint height, uint spacing)
	: width(width), height(height), spacing(spacing)
{
	TileSet::Create();
	PathFinder::Create();

	GenerateTileMap();

	vertices.assign(4, VertexTile());
	vertices[0].position = Values::ZeroVec3;
	vertices[1].position = Vector3(0.0f, (float)spacing, 0.0f);
	vertices[2].position = Vector3((float)spacing, 0.0f, 0.0f);
	vertices[3].position = Vector3((float)spacing, (float)spacing, 0.0f);

	vertices[0].uv2 = Vector2(0, 1);
	vertices[1].uv2 = Vector2(0, 0);
	vertices[2].uv2 = Vector2(1, 1);
	vertices[3].uv2 = Vector2(1, 0);

	indices.assign(6, uint());
	indices = { 0, 1, 2, 2, 1, 3 };

	vb = new VertexBuffer();
	vb->Create(vertices, D3D11_USAGE_DYNAMIC);

	ib = new IndexBuffer();
	ib->Create(indices, D3D11_USAGE_IMMUTABLE);

	vs = new VertexShader();
	vs->Create(ShaderPath + L"VertexTile.hlsl", "VS");

	ps = new PixelShader();
	ps->Create(ShaderPath + L"VertexTile.hlsl", "PS");

	il = new InputLayout();
	il->Create(VertexTile::descs, VertexTile::count, vs->GetBlob());

	wb = new WorldBuffer();
	wb->SetWorld(world);

	tb = new TileBuffer();
	
}

TMap::~TMap()
{
	SAFE_DELETE(tb);

	TileSet::Delete();
	PathFinder::Delete();
	for (uint y = 0; y < height; y++)
		SAFE_DELETE_ARRAY(tiles[y]);
	SAFE_DELETE_ARRAY(tiles);
	SAFE_DELETE(wb);
	SAFE_DELETE(il);
	SAFE_DELETE(vs);
	SAFE_DELETE(ps);
	SAFE_DELETE(ib);
	SAFE_DELETE(vb);
}

void TMap::Update()
{
	Vector3 mPos = Mouse::Get()->GetPosition();
	Tile* tile = GetTile(mPos);

	if (tile != nullptr)
	{
		tb->SetTileIndex(tile->GetIndex());
	}

	if (Mouse::Get()->Press(0))
	{
		if (tile != nullptr)
		{
			//tile->color = Values::Red;

			Vector2 startUV = TileSet::Get()->selectedStartUV;
			Vector2 endUV = startUV + TileSet::Get()->texelTileSize;
			tile->SetStartUV(startUV);
			tile->SetEndUV(endUV);
			if (mode == Redcell)
			{
				tile->SetIsWalkable(false);
			}
		}
	}
	if (Keyboard::Get()->Down(VK_SPACE))
	{
		//Build();
		//// temp
		//FindPath(nullptr, nullptr);
		SaveTileInfos();
	}
}

void TMap::Render()
{
	vb->SetIA();
	ib->SetIA();
	il->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vs->SetShader();
	ps->SetShader();
	DC->PSSetShaderResources(0, 1, &TileSet::Get()->tileSRV);
	tb->SetPSBuffer(0);
	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			Tile& tile = tiles[y][x];
			{
				MapVertexBuffer();
				{
					for (VertexTile& v : vertices)
					{
						v.color = tile.GetColor();
						v.bWalkable = tile.GetIsWalkable();
						v.index = tile.GetIndex();
					}
					vertices[0].uv = Vector2(tile.GetStartUV().x, tile.GetEndUV().y);
					vertices[1].uv = tile.GetStartUV();
					vertices[2].uv = tile.GetEndUV();
					vertices[3].uv = Vector2(tile.GetEndUV().x, tile.GetStartUV().y);

				}
				UnmapVertexBuffer();
			}
			world =  DxMath::Translation(tile.GetPosition());
			wb->SetWorld(world);
			wb->SetVSBuffer(0);
			DC->DrawIndexed(ib->GetCount(), 0, 0);
		}
	}
}

void TMap::GenerateTileMap()
{
	if (width == 0 || height == 0 || spacing == 0)
		assert(false);
	uint tileIndex = 0;
	tiles = new Tile*[height];
	for (uint y = 0; y < height; y++)
	{
		tiles[y] = new Tile[width];
		for (uint x = 0; x < width; x++)
		{
			tiles[y][x].SetPosition(Vector3((float)(x *spacing), (float)(y * spacing), 0.0f));
			tiles[y][x].SetIsWalkable(true);
			tiles[y][x].SetIndex(tileIndex++);
		}
	}
}

void TMap::MapVertexBuffer()
{
	DC->Map(vb->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
}

void TMap::UnmapVertexBuffer()
{
	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	DC->Unmap(vb->GetResource(), 0);
}

void TMap::GUI()
{
	TileSet::Get()->GUI();

	ImGui::Begin("TileMap");
	{
		ImGui::RadioButton("Normal", (int*)&mode, 0);
		ImGui::RadioButton("Redcell", (int*)&mode, 1);
	}
	ImGui::End();
}

Tile * TMap::GetTile(Vector3 mPos)
{
	uint x = (int)mPos.x / spacing;
	uint y = (int)mPos.y / spacing;

	if (x < 0 || x >= width || y < 0 || y >= height)
		return nullptr;

	return &tiles[y][x];
}

void TMap::Save()
{
	/*FileStream * f = new FileStream(TilePath + "main.tmap", FILE_STREAM_WRITE);

	for (uint y = 0; y < height; y++)
		for (uint x = 0; x < width; x++)
			f->Write(tiles[y][x]);

	SAFE_DELETE(f);*/
}

void TMap::Load()
{
	/*FileStream * r = new FileStream(TilePath + "main.tmap", FILE_STREAM_READ);

	for (uint y = 0; y < height; y++)
		for (uint x = 0; x < width; x++)
			tiles[y][x] = r->Read<Tile>();

	SAFE_DELETE(r);*/
}

void TMap::Build()
{
	for (uint y = 0; y < height; y++)
		for (uint x = 0; x < width; x++)
			tiles[y][x].Release();

	int newX = 0, newY = 0;
	Tile * child = nullptr;
	Tile* current = nullptr;

	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			current = &tiles[y][x];
			for (int i = -1; i < 2; i++)
			{
				newY = y + i;
				for (int j = -1; j < 2; j++)
				{
					newX = x + j;
					if (newY > -1 && newY < (int)height
						&& newX > -1 && newX < (int)width)
					{
						child = &tiles[newY][newX];
						bool isWalkable = child->GetIsWalkable();
						if (child->GetIsWalkable() == true
							&& current != child
							&& (newX == x || newY == y))
						{
							tiles[y][x].AddChild(make_pair(child, (float)spacing));
						}
					}

				}
			}

		}// for(x)
	} // for(y)
}

void TMap::FindPath(Tile * start, Tile * end)
{
	vector<Tile*> path;

	bool result = PathFinder::Get()->GetPath(&tiles[0][0], &tiles[height - 1][width - 1], path);

	if (result == true)
	{
		for (Tile* node : path)
		{
			node->SetColor(Values::Green);
		}
	}
}

void TMap::SaveTileInfos()
{
	Json::Value root;

	for (uint y = 0; y < height; y++)
	{
		for (uint x = 0; x < width; x++)
		{
			Tile& tile = tiles[y][x];
			Json::Value tileNode;
			string key = "Tile" + to_string(tile.GetIndex());

			Json::Value position;
			Vector3 pos = tile.GetPosition();
			Json::SetValue(position, "Position", pos);

			Json::Value color;
			Color col = tile.GetColor();
			Json::SetValue(color, "Color", col);

			Json::Value startUV;
			Vector2 sUV = tile.GetStartUV();
			Json::SetValue(startUV, "StartUV", sUV);

			Json::Value endUV;
			Vector2 eUV = tile.GetEndUV();
			Json::SetValue(endUV, "EndUV", eUV);


			tileNode["Position"] = position;
			tileNode["Color"] = color;
			tileNode["StartUV"] = startUV;
			tileNode["EndUV"] = endUV;

			root[key.c_str()] = tileNode;
		}
	}
	Json::WriteData(JsonPath + L"TileData.json", &root);
}
