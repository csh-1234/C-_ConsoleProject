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
		_name = "������";							// �̸�
		_monsterType = MonsterType::SLIME;	// ���� ����(�÷��̾�, ����)
		_hp = 50;							// ���� ü��
		_mp = 10;							// �⺻ ����
		_atk = 2;							// �⺻ ���ݷ�
		_def = 1;							// �⺻ ����
		_criRate = 5;						// �⺻ ũ��Ƽ�� Ȯ��
		_criDamage = 100;					// �⺻ ũ��Ƽ�� ������
		_avoidRate = 5;					// �⺻ ȸ����
		_speed = 1;						// �⺻ �ӵ�
		_money = 10;						// ������
	}
	~Slime() {}
};