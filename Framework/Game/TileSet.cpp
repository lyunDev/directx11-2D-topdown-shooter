#include "Framework.h"
#include "TileSet.h"

void TileSet::GUI()
{
	ImGui::Begin("TileSet");
	{
		int count = 0;
		for (uint y = 0; y < tileYCount; y++)
		{
			for (uint x = 0; x < tileXCount; x++)
			{
				float startX = texelTileSize.x * x; 
				float startY = texelTileSize.y * y;

				ImGui::PushID(count);
				if (ImGui::ImageButton
				(
					tileSRV,
					ImVec2(40, 40),
					ImVec2(startX, startY),
					ImVec2(startX + texelTileSize.x, startY + texelTileSize.y)))
				{
					selectedStartUV = Vector2(startX, startY);
				} // ImageButton
				count++;
				ImGui::PopID();
				if (count % 4 != 0)
					ImGui::SameLine();
			} // for(x)
		} // for(y)
	} // Begin
	ImGui::End();
}

TileSet::TileSet()
{
	Texture2D* tex = new Texture2D(TexturePath + L"TileMap.jpg");
	tileSRV = tex->GetSRV();
	SAFE_DELETE(tex);

	tileXCount = 10;
	tileYCount = 18;

	texelTileSize = Vector2(1 / (float)tileXCount, 1 / (float)tileYCount);

}

TileSet::~TileSet()
{
}
