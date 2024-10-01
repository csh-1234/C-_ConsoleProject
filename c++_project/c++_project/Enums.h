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
	NONE = 3,
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

