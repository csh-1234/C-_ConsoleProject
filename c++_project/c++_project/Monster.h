#pragma once
#include "Creature.h"
#include "Enums.h"
class Monster : public Creature
{
public:
	Monster(MonsterType monsterType) : Creature(MONSTER), _monsterType(monsterType) {}
	~Monster() {}

protected:
	MonsterType _monsterType;
};
class Slime : public Monster
{
public:
	Slime() : Monster(MonsterType::SLIME)
	{
		_name = "슬라임";							// 이름
		_monsterType = MonsterType::SLIME;	// 유닛 종류(플레이어, 몬스터)
		_hp = 50;							// 기초 체력
		_mp = 10;							// 기본 마나
		_atk = 2;							// 기본 공격력
		_def = 1;							// 기본 방어력
		_criRate = 5;						// 기본 크리티컬 확률
		_criDamage = 100;					// 기본 크리티컬 데미지
		_avoidRate = 5;					// 기본 회피율
		_speed = 1;						// 기본 속도
		_money = 10;						// 소지금
	}
	~Slime() {}
};