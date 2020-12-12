#pragma once

namespace EditData
{
	static const int MaxPath = 256;
	struct UnitData
	{
		Texture2D * tex;
		char texturePath[256];
		int maxHp;
		int moveSpeed;
		float size[3]; // vector3
		float firePosOffset[3]; // vector3
	};
	struct UnitBullet
	{
		Texture2D * tex;
		char texturePath[256];
		int damage;
		int speed;
		float size[3];
		float collisionSize[3];
	};
	struct UnitMuzzleFlash
	{
		Texture2D * tex;
		char texturePath[256];
		float size[3];
	};


	struct RespawnData
	{
		float delay;
		unsigned int poolMaximum;
		float startRespawnTime;
		float endRespawnTime;
	};

	enum class UnitIndex
	{
		Clone = 0,
		Assault,
		BrownAssault,
		RedAssault,
		Cannoneer,
		Engineer,
		Medic,
		Nebulizer,
		Pyro,
		Sniper,
		Tech,
		MAX
	};

};