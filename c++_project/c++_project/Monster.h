#pragma once
#include "Creature.h"
#include "Enums.h"
class Monster : public Creature
{
public:
	Monster(MonsterType monsterType);
	
	~Monster() {}

	MonsterType GetMonsterType();

protected:
	MonsterType _monsterType;
};
