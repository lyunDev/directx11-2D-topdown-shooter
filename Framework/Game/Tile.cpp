#include "Framework.h"
#include "Tile.h"
#include "Utilities/FileStream.h"

bool PathFinder::GetPath(Tile * start, Tile * end, vector<Tile*>& path)
{
	Clear();

	Tile* currentNode = nullptr;
	Tile* childNode = nullptr;
	float f = 0.0f, g = 0.0f, h = 0.0f;
	openList.push_back(start);
	start->isOpen = true;

	while (!openList.empty())
	{
		sort(openList.begin(), openList.end(),
			[](Tile* lhs, Tile* rhs) -> bool
		{
			return lhs->GetF() > rhs->GetF();
			//lhs가 rhs보다 앞에 올 조건
		});

		currentNode = openList.back();
		openList.pop_back();
		currentNode->isOpen = false;

		closeList.push_back(currentNode);
		currentNode->isClose = true;

		if (currentNode == end)
		{
			ReConstructPath(currentNode, path);
			return true;
		}

		for (ChildNode& child : currentNode->childs)
		{
			childNode = child.first;

			g = currentNode->g + child.second;

			if (childNode->isClose)
				continue;

			bool isCheck = true;
			isCheck &= childNode->isOpen;
			isCheck &= childNode->g < g;
			if (isCheck)
				continue;

			h = childNode->GetDistance(end);
			f = g + h;

			childNode->f = f;
			childNode->g = g;
			childNode->h = h;
			childNode->parentNode = currentNode;

			if (childNode->isOpen == false)
			{
				openList.push_back(childNode);
				childNode->isOpen = true;
			}
		}
	}

	return false;
}

void PathFinder::ReConstructPath(Tile * node, vector<Tile*>& path)
{
	Tile* parent = node->parentNode;
	path.push_back(node);

	while (parent != nullptr)
	{
		path.push_back(parent);
		parent = parent->parentNode;
	}
}

void PathFinder::Clear()
{
	openList.clear();
	closeList.clear();
}

float Tile::GetDistance(Tile * node)
{
	float distX = abs(position.x - node->position.x);
	float distY = abs(position.y - node->position.y);

	return distX + distY;
}

//void Tile::SaveTile(FileStream * w)
//{
//	w->Write(position);
//	w->Write(color);
//	w->Write(startUV);
//	w->Write(endUV);
//	w->Write(isWalkable);
//	w->WriteString(spriteName);
//}
//
//void Tile::ReadTile(FileStream * r)
//{
//	position = r->Read<Vector3>();
//	color = r->Read<Color>();
//	startUV = r->Read<Vector2>();
//	endUV = r->Read<Vector2>();
//	isWalkable = r->Read<bool>();
//	spriteName = r->ReadString();
//}
