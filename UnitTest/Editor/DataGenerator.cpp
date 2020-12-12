#include "stdafx.h"
#include "DataGenerator.h"



EditData::UnitData DataGenerator::unitDatas[(unsigned int)EditData::UnitIndex::MAX];
EditData::UnitBullet DataGenerator::unitBullets[(unsigned int)EditData::UnitIndex::MAX];
EditData::UnitMuzzleFlash DataGenerator::unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::MAX];
EditData::RespawnData DataGenerator::unitRespawns[(unsigned int)EditData::UnitIndex::MAX];


DataGenerator::DataGenerator()
{
}

DataGenerator::~DataGenerator()
{
}

void DataGenerator::SaveUnitData()
{
	Json::Value root;
	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitDataNode;
		string key = unitNames[i];



		Json::Value texturePath;
		string texPath(unitDatas[i].texturePath);
		Json::SetValue(unitDataNode, "TexturePath", texPath);

		Json::Value maxHp;
		Json::SetValue(unitDataNode, "MaxHP", unitDatas[i].maxHp);

		Json::Value moveSpeed;
		Json::SetValue(unitDataNode, "MoveSpeed", unitDatas[i].moveSpeed);

		Json::Value size;
		Vector3 sizeVec;
		sizeVec.x = unitDatas[i].size[0];
		sizeVec.y = unitDatas[i].size[1];
		sizeVec.z = unitDatas[i].size[2];
		Json::SetValue(unitDataNode, "Size", sizeVec);

		Json::Value firePosOffset;
		Vector3 firePosOffsetVec;
		firePosOffsetVec.x = unitDatas[i].firePosOffset[0];
		firePosOffsetVec.y = unitDatas[i].firePosOffset[1];
		firePosOffsetVec.z = unitDatas[i].firePosOffset[2];
		Json::SetValue(unitDataNode, "FirePosOffset", firePosOffsetVec);

		/*unitDataNode["TexturePath"] = texturePath;
		unitDataNode["MaxHP"] = maxHp;
		unitDataNode["MoveSpeed"] = moveSpeed;
		unitDataNode["Size"] = size;
		unitDataNode["FirePosOffset"] = firePosOffset;
*/
		root[key.c_str()] = unitDataNode;
	}
	Json::WriteData(UNITDATA_PATH, &root);
}

void DataGenerator::ReadUnitData()
{
	Json::Value root;
	Json::ReadData(UNITDATA_PATH, &root);
	
	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitData = root[unitNames[i]];
		string texPath;

		//auto str = path.asString();
		Json::Value path;
		for (auto& var : unitData["TexturePath"])
		{
			texPath = var.asString();
		}
		//Json::GetValue(unitData, "TexturePath", texPath);
		strcpy(unitDatas[i].texturePath, texPath.c_str());
		
		int maxHp;
		int moveSpeed;
		Vector3 size;
		Vector3 firePosOffset;
		Json::GetValue(unitData, "MaxHP", maxHp);
		Json::GetValue(unitData, "MoveSpeed", moveSpeed);
		Json::GetValue(unitData, "Size", size);
		Json::GetValue(unitData, "FirePosOffset", firePosOffset);

		unitDatas[i].maxHp = maxHp;
		unitDatas[i].moveSpeed = moveSpeed;
		unitDatas[i].size[0] = size.x;
		unitDatas[i].size[1] = size.y;
		unitDatas[i].size[2] = size.z;
		unitDatas[i].firePosOffset[0] = firePosOffset.x;
		unitDatas[i].firePosOffset[1] = firePosOffset.y;
		unitDatas[i].firePosOffset[2] = firePosOffset.z;

	}

}

void DataGenerator::SaveUnitBullet()
{
	Json::Value root;
	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitBullet;
		string key = unitNames[i];

		string texPath(unitBullets[i].texturePath);
		Json::SetValue(unitBullet, "TexturePath", texPath);
		Json::SetValue(unitBullet, "Damage", unitBullets[i].damage);
		Json::SetValue(unitBullet, "Speed", unitBullets[i].speed);
		Vector3 size;
		size.x = unitBullets[i].size[0];
		size.y = unitBullets[i].size[1];
		size.z = unitBullets[i].size[2];
		Json::SetValue(unitBullet, "Size", size);
		Vector3 collisionSize;
		collisionSize.x = unitBullets[i].collisionSize[0];
		collisionSize.y = unitBullets[i].collisionSize[1];
		collisionSize.z = unitBullets[i].collisionSize[2];
		Json::SetValue(unitBullet, "CollisionSize", collisionSize);

		root[key.c_str()] = unitBullet;
	}
	Json::WriteData(UNITBULLET_PATH, &root);
}

void DataGenerator::ReadUnitBullet()
{
	Json::Value root;
	Json::ReadData(UNITBULLET_PATH, &root);

	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitBullet = root[unitNames[i]];
		string texPath;

		for (auto& var : unitBullet["TexturePath"])
		{
			texPath = var.asString();
		}
		strcpy(unitBullets[i].texturePath, texPath.c_str());

		int damage;
		int speed;
		Vector3 size;
		Vector3 collisionSize;

		Json::GetValue(unitBullet, "Damage", damage);
		Json::GetValue(unitBullet, "Speed", speed);
		Json::GetValue(unitBullet, "Size", size);
		Json::GetValue(unitBullet, "CollisionSize", collisionSize);

		unitBullets[i].damage = damage;
		unitBullets[i].speed = speed;
		unitBullets[i].size[0] = size.x;
		unitBullets[i].size[1] = size.y;
		unitBullets[i].size[2] = size.z;
		unitBullets[i].collisionSize[0] = collisionSize.x;
		unitBullets[i].collisionSize[1] = collisionSize.y;
		unitBullets[i].collisionSize[2] = collisionSize.z;
	}
}

void DataGenerator::SaveUnitMuzzleFlash()
{
	Json::Value root;
	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitMuzzleFlash;
		string key = unitNames[i];

		string texPath(unitMuzzleFlashes[i].texturePath);
		Json::SetValue(unitMuzzleFlash, "TexturePath", texPath);
		Vector3 size;
		size.x = unitMuzzleFlashes[i].size[0];
		size.y = unitMuzzleFlashes[i].size[1];
		size.z = unitMuzzleFlashes[i].size[2];
		Json::SetValue(unitMuzzleFlash, "Size", size);
		
		root[key.c_str()] = unitMuzzleFlash;
	}
	Json::WriteData(UNITMUZZLEFLASH_PATH, &root);
}

void DataGenerator::ReadUnitMuzzleFlash()
{
	Json::Value root;
	Json::ReadData(UNITMUZZLEFLASH_PATH, &root);
	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitMuzzleFlash = root[unitNames[i]];

		string texPath;
		for (auto& var : unitMuzzleFlash["TexturePath"])
		{
			texPath = var.asString();
		}
		strcpy(unitMuzzleFlashes[i].texturePath, texPath.c_str());

		Vector3 size;
		Json::GetValue(unitMuzzleFlash, "Size", size);
		unitMuzzleFlashes[i].size[0] = size.x;
		unitMuzzleFlashes[i].size[1] = size.y;
		unitMuzzleFlashes[i].size[2] = size.z;
	}
}

void DataGenerator::SaveUnitRespawn()
{
	Json::Value root;
	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitRespawn;
		string key = unitNames[i];

		float delay = unitRespawns[i].delay;
		int poolMaximum = unitRespawns[i].poolMaximum;
		float startRespawnTime = unitRespawns[i].startRespawnTime;
		float endRespawnTime = unitRespawns[i].endRespawnTime;

		Json::SetValue(unitRespawn, "Delay", delay);
		Json::SetValue(unitRespawn, "PoolMaximum", poolMaximum);
		Json::SetValue(unitRespawn, "StartRespawnTime", startRespawnTime);
		Json::SetValue(unitRespawn, "EndRespawnTime", endRespawnTime);

		root[key.c_str()] = unitRespawn;
	}
	Json::WriteData(UNITRESPAWN_PATH, &root);
}

void DataGenerator::ReadUnitRespawn()
{
	Json::Value root;
	Json::ReadData(UNITRESPAWN_PATH, &root);
	for (int i = 0; i < (int)EditData::UnitIndex::MAX; i++)
	{
		Json::Value unitRespawn = root[unitNames[i]];

		float delay;
		int poolMaximum;
		float startRespawnTime;
		float endRespawnTime;
		Json::GetValue(unitRespawn, "Delay", delay);
		Json::GetValue(unitRespawn, "PoolMaximum", poolMaximum);
		Json::GetValue(unitRespawn, "StartRespawnTime", startRespawnTime);
		Json::GetValue(unitRespawn, "EndRespawnTime", endRespawnTime);
		unitRespawns[i].delay = delay;
		unitRespawns[i].poolMaximum = poolMaximum;
		unitRespawns[i].startRespawnTime = startRespawnTime;
		unitRespawns[i].endRespawnTime = endRespawnTime;
	}
}
