#include "Monster.h"

Monster::Monster(MonsterType monsterType) : Creature(MONSTER), _monsterType(monsterType)
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
		_money = 50;						// ������
		_exp = 50;
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
		_money = 100;						// ������
		_exp = 80;
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
		_money = 300;						// ������
		_exp = 150;
	}
	else if (monsterType == MonsterType::INVISIBLEDRAGON)
	{
		_name = "���� �巡��";							// �̸�
		_monsterType = MonsterType::INVISIBLEDRAGON;	// ���� ����(�÷��̾�, ����)
		_hp = 10000;							// ���� ü��
		_mp = 10000;							// �⺻ ����
		_atk = 100;							// �⺻ ���ݷ�
		_def = 50;							// �⺻ ����
		_criRate = 30;						// �⺻ ũ��Ƽ�� Ȯ��
		_criDamage = 100;					// �⺻ ũ��Ƽ�� ������
		_money = 1000000;						// ������
		_exp = 100000;
	}
}

MonsterType Monster::GetMonsterType()
{
	return _monsterType;
}
