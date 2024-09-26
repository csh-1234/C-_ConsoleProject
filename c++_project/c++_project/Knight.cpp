#include "Knight.h"
#include "Player.h"

Knight::Knight(string name) : Player(CharacterClass::KNIGHT)
{
	_name = name;					// 이름
	_characterClass = CharacterClass::KNIGHT;	// 유닛 종류(플레이어, 몬스터)
	_maxHp = 200;				// 최대 체력
	_hp = 200;					// 기초 체력
	_maxMp = 100;				// 최대 마나
	_mp = 100;					// 기본 마나
	_atk = 10;					// 기본 공격력
	_def = 5;					// 기본 방어력
	_criRate = 10;				// 기본 크리티컬 확률
	_criDamage = 150;			// 기본 크리티컬 데미지
	_avoidRate = 10;			// 기본 회피율
	_speed = 10;				// 기본 속도
	_money = 10000;				// 소지금
}

Knight::~Knight()
{
}
