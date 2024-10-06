#pragma once
#pragma once

#include <iostream>
#include <vector>
#include "Creature.h"
#include "Enums.h"
#include "Skill.h"
using namespace std;

class Player : public Creature
{
public:
	Player(string playerName);
	~Player();

	void useSkill(Creature* Caster, Creature* Target, int index);
};



