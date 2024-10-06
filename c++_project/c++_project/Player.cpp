#include "Player.h"

Player::Player(string playerName) : Creature(PLAYER)
{
	_name = playerName;					// �̸�
	_maxHp = 200;				// �ִ� ü��
	_hp = 200;					// ���� ü��
	_maxMp = 100;				// �ִ� ����
	_mp = 100;					// �⺻ ����
	_atk = 10;					// �⺻ ���ݷ�
	_def = 5;					// �⺻ ����
	_criRate = 10;				// �⺻ ũ��Ƽ�� Ȯ��
	_criDamage = 150;			// �⺻ ũ��Ƽ�� ������
	_money = 10000;				// ������
	_exp = 0;
	_level = 1;
}

Player::~Player()
{
}

void Player::useSkill(Creature* Caster, Creature* Target, int index)
{
	if (index >= 0 && index < _ActiveSkillList.size())
	{
		if (_ActiveSkillList[index]->getSkillType() == SkillType::Active)
		{
			_ActiveSkillList[index]->ActiveSkillCast(Caster, Target);
		}
		else if (_ActiveSkillList[index]->getSkillType() == SkillType::Buff)
		{
			_ActiveSkillList[index]->BuffSkillCast(Caster);
		}
		//else // passive
		//{
		//	cout << "�нú� ��ų�� �ڵ����� �ߵ��մϴ�." << endl;
		//}
	}
}

