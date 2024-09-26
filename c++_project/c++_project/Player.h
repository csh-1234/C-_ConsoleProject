#pragma once
#pragma once

#include <iostream>
#include <vector>
#include "Creature.h"
#include "Enums.h"
using namespace std;

class Player : public Creature
{
public:
	Player(CharacterClass characterClass);
	~Player();
protected:
	CharacterClass _characterClass;
};



