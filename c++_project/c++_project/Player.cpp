#include "Player.h"

Player::Player(string playerName) : Creature(PLAYER)
{
	_name = playerName;					// 이름
	_maxHp = 200;				// 최대 체력
	_hp = 200;					// 기초 체력
	_maxMp = 100;				// 최대 마나
	_mp = 100;					// 기본 마나
	_atk = 10;					// 기본 공격력
	_def = 5;					// 기본 방어력
	_criRate = 10;				// 기본 크리티컬 확률
	_criDamage = 150;			// 기본 크리티컬 데미지
	_money = 10000;				// 소지금
	_exp = 0;
	_level = 1;
}

Player::~Player()
{
}

