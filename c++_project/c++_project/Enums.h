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
	SLIME = 1,
	GOBLIN = 2,
	SKELETON = 3,
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