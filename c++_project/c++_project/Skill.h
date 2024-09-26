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
	int _skillCost; //마나 소비량
	string _skillInfo;
	bool _isActivate; //일단은 패시브 스킬에만 적용
};

class FireBall : public Skill
{
public:
	FireBall() : Skill()
	{
		_skillLevel = 1;
		_skillName = "파이어볼";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "화염구를 날려 적에게 ([공격력] X [스킬레벨] X 2 )피해를 입힌다.";
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
		cout << "[ " << casterName << " ]" << "이(가) [ " << targetName << " ] 에게 스킬 [ 파이어볼 ] 시전!" << endl;
		float damage = casterAtk * 2 * _skillLevel;

		if (damage < 0)
			damage = 0;

		if ((rand() % 100) + 1 <= casterCriRate) // 1 ~ 100
		{
			damage *= casterCriDamage / 100;
			cout << "[ " << casterName << " ]" << "이(가) " << targetName << " 에게 <<<<크리티컬>>>> " << damage << " 데미지를 입힘" << endl;
			cout << "[ " << targetName << " ]의 체력 : " << targetHp << " -> " << targetHp - damage << endl;
			Target->SetHp(targetHp - damage);
		}
		else
		{
			cout << "[ " << casterName << " ]" << "이(가) " << targetName << " 에게 " << damage << " 데미지를 입힘" << endl;
			cout << "[ " << targetName << " ]의 체력 : " << targetHp << " -> " << targetHp - damage << endl;
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
		_skillName = "공격력 증가 버프";
		_skillType = static_cast<int>(SkillType::Buff);
		_skillCost = 10;
		_skillInfo = "버프 시전자의 공격력을 ([스킬레벨] X 5) 향상시킨다.";
	}
	~ReinforceAtk() {}

	void BuffSkillCast(Creature* Caster)
	{
		int EnhancedAtk = Caster->GetAtk() + (5 * _skillLevel);
		string casterName = Caster->GetName();
		int casterAtk = Caster->GetAtk();

		Caster->SetMp(Caster->GetMp() - _skillCost);
		cout << "[ " << casterName << " ]" << "이(가) [ 버프스킬 [ 공격력 강화 ] 시전!" << endl;
		cout << "버프 시전자의 공격력이 " << 5 * _skillLevel << "만큼 증가합니다." << endl;
		cout << casterName << "의 공격력 : " << casterAtk << " => " << EnhancedAtk << endl;
		Caster->SetAtk(EnhancedAtk);

		//TODO 한 라운드가 끝나면 버프로 올라갔던 공격력을 돌려야함
		// 1. player 객체를 복사해서 사용한다. 라운드 종료후 원래 객체로 복귀
		// 2. 실제로 값을 카운트하고, 라운드가 끝나면 빼서 돌린다.
	}
};
class GreatStamina : public Skill
{
public:
	GreatStamina() : Skill()
	{
		_skillLevel = 1;
		_skillName = "강인한 체력";
		_skillType = static_cast<int>(SkillType::Passive);
		_skillCost = 0;
		_skillInfo = "스킬 소유자의 최대체력이 영구적으로 ([스킬레벨] X 10)증가합니다.";
	}
	~GreatStamina() {}

	void PassiveSkillCast(Creature* Caster)
	{
		if (!_isActivate) //혹시라도 실행될까바 2중보안
		{
			Caster->SetHp(Caster->GetHp() + (10 * _skillLevel));
			Caster->SetMaxHp(Caster->GetMaxHp() + (10 * _skillLevel));
			_isActivate = true;
		}
	}

	//TODO 스킬레벨 증가시 기존 패시브 말고 레벨업한 페시브로 적용해야함
private:

};
