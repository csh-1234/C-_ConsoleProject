#include "Player.h"

Player::Player(CharacterClass characterClass) : Creature(PLAYER)
{
	_characterClass = characterClass;
}

Player::~Player()
{
}

