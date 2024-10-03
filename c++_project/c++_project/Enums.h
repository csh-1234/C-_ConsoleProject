#pragma once
enum class CharacterClass
{
	KNIGHT = 1,
	MAGE = 2,
	ARCHER = 3,
	NONE = 4,
};
enum class MonsterType
{
	SLIME = 0,
	GOBLIN = 1,
	SKELETON = 2,
	INVISIBLEDRAGON = 3,
	NONE = 4,
};
enum UnitType
{
	PLAYER = 1,
	MONSTER = 2,
	NPC = 3,
	NONE = 4,
};
enum SkillType
{
	Passive,
	Active,
	Buff,
};
enum ItemType
{
	Potion,
	Equipment,
	Etc,
};
enum EquipmentType
{
	Weapon,
	Armor,
};

enum class EGameObject
{
	EMPTY = 0,
	WALL = 1,
	PLAYER = 2,
	TREE1 = 3,
	TREE2 = 4,
	MONSTER = 5,
	BOSSMONSTER = 6,
	NPC = 7,
	TILE1 = 8,
	PORTAL = 9,
};

enum class eMaps
{
	Village,
	Dungeon_1,
	Dungeon_2,
	BossRoom,
	test,
	None,	// 항상 맨끝에 둘 것.(개수 파악용)
};