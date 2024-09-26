#pragma once
#include <iostream>
#include "Creature.h"
#include "Enums.h"
using namespace std;

class Skill
{
public:
	Skill();
	~Skill();

	virtual void ActiveSkillCast(Creature* Attacker, Creature* Defender) {};
	virtual void PassiveSkillCast(Creature* Caster) {};
	virtual void BuffSkillCast(Creature* Caster) {};

#pragma region property
	string GetSkillName();
	int GetSkillType();
	int GetSkillCost();
	bool GetIsActivate();
#pragma endregion
protected:
	int _skillLevel;
	string _skillName;
	int _skillType;
	int _skillCost; //���� �Һ�
	string _skillInfo;
	bool _isActivate; //�ϴ��� �нú� ��ų���� ����
};

class FireBall : public Skill
{
public:
	FireBall() : Skill()
	{
		_skillLevel = 1;
		_skillName = "���̾";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "ȭ������ ���� ������ ([���ݷ�] X [��ų����] X 2 )���ظ� ������.";
	}
	~FireBall() {}

	void ActiveSkillCast(Creature* Caster, Creature* Target)
	{
		string casterName = Caster->GetName();
		int casterAtk = Caster->GetAtk();
		int casterCriRate = Caster->GetCriRate();
		int casterCriDamage = Caster->GetCriDamage();

		string targetName = Target->GetName();
		int targetHp = Target->GetHp();
		int targetDef = Target->GetDef();

		Caster->SetMp(Caster->GetMp() - _skillCost);
		cout << "[ " << casterName << " ]" << "��(��) [ " << targetName << " ] ���� ��ų [ ���̾ ] ����!" << endl;
		float damage = casterAtk * 2 * _skillLevel;

		if (damage < 0)
			damage = 0;

		if ((rand() % 100) + 1 <= casterCriRate) // 1 ~ 100
		{
			damage *= casterCriDamage / 100;
			cout << "[ " << casterName << " ]" << "��(��) " << targetName << " ���� <<<<ũ��Ƽ��>>>> " << damage << " �������� ����" << endl;
			cout << "[ " << targetName << " ]�� ü�� : " << targetHp << " -> " << targetHp - damage << endl;
			Target->SetHp(targetHp - damage);
		}
		else
		{
			cout << "[ " << casterName << " ]" << "��(��) " << targetName << " ���� " << damage << " �������� ����" << endl;
			cout << "[ " << targetName << " ]�� ü�� : " << targetHp << " -> " << targetHp - damage << endl;
			Target->SetHp(targetHp - damage);
		}
	}
};
class ReinforceAtk : public Skill
{
public:
	ReinforceAtk() : Skill()
	{
		_skillLevel = 1;
		_skillName = "���ݷ� ���� ����";
		_skillType = static_cast<int>(SkillType::Buff);
		_skillCost = 10;
		_skillInfo = "���� �������� ���ݷ��� ([��ų����] X 5) ����Ų��.";
	}
	~ReinforceAtk() {}

	void BuffSkillCast(Creature* Caster)
	{
		int EnhancedAtk = Caster->GetAtk() + (5 * _skillLevel);
		string casterName = Caster->GetName();
		int casterAtk = Caster->GetAtk();

		Caster->SetMp(Caster->GetMp() - _skillCost);
		cout << "[ " << casterName << " ]" << "��(��) [ ������ų [ ���ݷ� ��ȭ ] ����!" << endl;
		cout << "���� �������� ���ݷ��� " << 5 * _skillLevel << "��ŭ �����մϴ�." << endl;
		cout << casterName << "�� ���ݷ� : " << casterAtk << " => " << EnhancedAtk << endl;
		Caster->SetAtk(EnhancedAtk);

		//TODO �� ���尡 ������ ������ �ö󰬴� ���ݷ��� ��������
		// 1. player ��ü�� �����ؼ� ����Ѵ�. ���� ������ ���� ��ü�� ����
		// 2. ������ ���� ī��Ʈ�ϰ�, ���尡 ������ ���� ������.
	}
};
class GreatStamina : public Skill
{
public:
	GreatStamina() : Skill()
	{
		_skillLevel = 1;
		_skillName = "������ ü��";
		_skillType = static_cast<int>(SkillType::Passive);
		_skillCost = 0;
		_skillInfo = "��ų �������� �ִ�ü���� ���������� ([��ų����] X 10)�����մϴ�.";
	}
	~GreatStamina() {}

	void PassiveSkillCast(Creature* Caster)
	{
		if (!_isActivate) //Ȥ�ö� ����ɱ�� 2�ߺ���
		{
			Caster->SetHp(Caster->GetHp() + (10 * _skillLevel));
			Caster->SetMaxHp(Caster->GetMaxHp() + (10 * _skillLevel));
			_isActivate = true;
		}
	}

	//TODO ��ų���� ������ ���� �нú� ���� �������� ��ú�� �����ؾ���
private:

};
