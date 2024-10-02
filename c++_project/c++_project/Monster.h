#pragma once
#include "Creature.h"
#include "Enums.h"
class Monster : public Creature
{
public:
	Monster(MonsterType monsterType) : Creature(MONSTER), _monsterType(monsterType) 
	{
		if (monsterType == MonsterType::SLIME)
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
			_money = 50;						// ������
		}
		else if (monsterType == MonsterType::GOBLIN)
		{
			_name = "���";							// �̸�
			_monsterType = MonsterType::GOBLIN;	// ���� ����(�÷��̾�, ����)
			_hp = 80;							// ���� ü��
			_mp = 20;							// �⺻ ����
			_atk = 3;							// �⺻ ���ݷ�
			_def = 2;							// �⺻ ����
			_criRate = 7;						// �⺻ ũ��Ƽ�� Ȯ��
			_criDamage = 100;					// �⺻ ũ��Ƽ�� ������
			_avoidRate = 10;					// �⺻ ȸ����
			_speed = 1;						// �⺻ �ӵ�
			_money = 100;						// ������
		}
		else if (monsterType == MonsterType::SKELETON)
		{
			_name = "���̷���";							// �̸�
			_monsterType = MonsterType::SKELETON;	// ���� ����(�÷��̾�, ����)
			_hp = 120;							// ���� ü��
			_mp = 30;							// �⺻ ����
			_atk = 5;							// �⺻ ���ݷ�
			_def = 1;							// �⺻ ����
			_criRate = 10;						// �⺻ ũ��Ƽ�� Ȯ��
			_criDamage = 100;					// �⺻ ũ��Ƽ�� ������
			_avoidRate = 10;					// �⺻ ȸ����
			_speed = 1;						// �⺻ �ӵ�
			_money = 300;						// ������
		}
	
	}
	~Monster() {}
	
	MonsterType GetMonsterType() { return _monsterType; }

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