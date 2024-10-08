#include "Monster.h"

Monster::Monster(MonsterType monsterType) : Creature(MONSTER), _monsterType(monsterType)
{
	if (monsterType == MonsterType::SLIME)
	{
		_name = "슬라임";							// 이름
		_monsterType = MonsterType::SLIME;	// 유닛 종류(플레이어, 몬스터)
		_hp = 50;							// 기초 체력
		_mp = 10;							// 기본 마나
		_atk = 2;							// 기본 공격력
		_def = 1;							// 기본 방어력
		_criRate = 5;						// 기본 크리티컬 확률
		_criDamage = 100;					// 기본 크리티컬 데미지
		_money = 50;						// 소지금
		_exp = 50;
	}
	else if (monsterType == MonsterType::GOBLIN)
	{
		_name = "고블린";							// 이름
		_monsterType = MonsterType::GOBLIN;	// 유닛 종류(플레이어, 몬스터)
		_hp = 80;							// 기초 체력
		_mp = 20;							// 기본 마나
		_atk = 3;							// 기본 공격력
		_def = 2;							// 기본 방어력
		_criRate = 7;						// 기본 크리티컬 확률
		_criDamage = 100;					// 기본 크리티컬 데미지
		_money = 100;						// 소지금
		_exp = 80;
	}
	else if (monsterType == MonsterType::SKELETON)
	{
		_name = "스켈레톤";							// 이름
		_monsterType = MonsterType::SKELETON;	// 유닛 종류(플레이어, 몬스터)
		_hp = 120;							// 기초 체력
		_mp = 30;							// 기본 마나
		_atk = 5;							// 기본 공격력
		_def = 1;							// 기본 방어력
		_criRate = 10;						// 기본 크리티컬 확률
		_criDamage = 100;					// 기본 크리티컬 데미지
		_money = 300;						// 소지금
		_exp = 150;
	}
	else if (monsterType == MonsterType::INVISIBLEDRAGON)
	{
		_name = "투명 드래곤";							// 이름
		_monsterType = MonsterType::INVISIBLEDRAGON;	// 유닛 종류(플레이어, 몬스터)
		_hp = 10000;							// 기초 체력
		_mp = 10000;							// 기본 마나
		_atk = 100;							// 기본 공격력
		_def = 50;							// 기본 방어력
		_criRate = 30;						// 기본 크리티컬 확률
		_criDamage = 100;					// 기본 크리티컬 데미지
		_money = 1000000;						// 소지금
		_exp = 100000;
	}
}

MonsterType Monster::GetMonsterType()
{
	return _monsterType;
}
