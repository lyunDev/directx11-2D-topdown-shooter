#pragma once
#include "EditData.h"

#define UNITDATA_PATH JsonPath + L"UnitDatas.json"
#define UNITBULLET_PATH JsonPath + L"UnitBullets.json"
#define UNITMUZZLEFLASH_PATH JsonPath + L"UnitMuzzleFlashes.json"
#define UNITRESPAWN_PATH JsonPath + L"UnitRespawns.json"

#define ASSAULT_UNIT_DATA DataGenerator::unitDatas[(unsigned int)EditData::UnitIndex::Assault]
#define CLONE_UNIT_DATA DataGenerator::unitDatas[(unsigned int)EditData::UnitIndex::Clone]
#define CANNONEER_UNIT_DATA DataGenerator::unitDatas[(unsigned int)EditData::UnitIndex::Cannoneer]
#define ENGINEER_UNIT_DATA DataGenerator::unitDatas[(unsigned int)EditData::UnitIndex::Engineer]
#define NEBULIZER_UNIT_DATA DataGenerator::unitDatas[(unsigned int)EditData::UnitIndex::Nebulizer]
#define SNIPER_UNIT_DATA DataGenerator::unitDatas[(unsigned int)EditData::UnitIndex::Sniper]

#define ASSAULT_BULLET_DATA DataGenerator::unitBullets[(unsigned int)EditData::UnitIndex::Assault]
#define CLONE_BULLET_DATA DataGenerator::unitBullets[(unsigned int)EditData::UnitIndex::Clone]
#define CANNONEER_BULLET_DATA DataGenerator::unitBullets[(unsigned int)EditData::UnitIndex::Cannoneer]
#define ENGINEER_BULLET_DATA DataGenerator::unitBullets[(unsigned int)EditData::UnitIndex::Engineer]
#define NEBULIZER_BULLET_DATA DataGenerator::unitBullets[(unsigned int)EditData::UnitIndex::Nebulizer]
#define SNIPER_BULLET_DATA DataGenerator::unitBullets[(unsigned int)EditData::UnitIndex::Sniper]

#define ASSAULT_MUZZLEFLASH_DATA DataGenerator::unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::Assault]
#define CLONE_MUZZLEFLASH_DATA DataGenerator::unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::Clone]
#define CANNONEER_MUZZLEFLASH_DATA DataGenerator::unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::Cannoneer]
#define ENGINEER_MUZZLEFLASH_DATA DataGenerator::unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::Engineer]
#define NEBULIZER_MUZZLEFLASH_DATA DataGenerator::unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::Nebulizer]
#define SNIPER_MUZZLEFLASH_DATA DataGenerator::unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::Sniper]

class DataGenerator
{
public :
	DataGenerator();
	~DataGenerator();

	void SaveUnitData();
	void ReadUnitData();

	void SaveUnitBullet();
	void ReadUnitBullet();

	void SaveUnitMuzzleFlash();
	void ReadUnitMuzzleFlash();

	void SaveUnitRespawn();
	void ReadUnitRespawn();

	static EditData::UnitData unitDatas[(unsigned int)EditData::UnitIndex::MAX];
	static EditData::UnitBullet unitBullets[(unsigned int)EditData::UnitIndex::MAX];
	static EditData::UnitMuzzleFlash unitMuzzleFlashes[(unsigned int)EditData::UnitIndex::MAX];
	static EditData::RespawnData unitRespawns[(unsigned int)EditData::UnitIndex::MAX];

	string unitNames[(unsigned int)EditData::UnitIndex::MAX] =
	{
		"Clone",
		"Assault",
		"BrownAssault",
		"RedAssault",
		"Cannoneer",
		"Engineer",
		"Medic",
		"Nebulizer",
		"Pyro",
		"Sniper",
		"Tech"
	};
};