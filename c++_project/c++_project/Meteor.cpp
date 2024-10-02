#include "Meteor.h"
#include "Creature.h"
#include <string>
#pragma warning(disable:4996)
Meteor::~Meteor()
{
}
vector<wstring> Meteor::ActiveSkillCast(Creature* Caster, Creature* TarGet)
{
	vector<wstring> SkillMessage;

	string casterName = Caster->GetName();
	int casterAtk = Caster->GetAtk();
	int casterCriRate = Caster->GetCriRate();
	int casterCriDamage = Caster->GetCriDamage();

	string tarGetName = TarGet->GetName();
	int tarGetHp = TarGet->GetHp();
	int tarGetDef = TarGet->GetDef();

	Caster->SetMp(Caster->GetMp() - _skillCost);
	wstring wstr(casterName.size(), L'\0');
	std::mbstowcs(&wstr[0], casterName.c_str(), casterName.size());
	wstring wstr2(tarGetName.size(), L'\0');
	std::mbstowcs(&wstr2[0], tarGetName.c_str(), tarGetName.size());

	SkillMessage.push_back(wstr + L"이(가)" + wstr2 + L" 에게 스킬 [ 메테오 ] 시전!");
	int damage = casterAtk * 100 * _skillLevel;

	if (damage < 0)
		damage = 0;

	if ((rand() % 100) + 1 <= casterCriRate) // 1 ~ 100
	{
		damage *= 1.5;
		SkillMessage.push_back(wstr + L"이(가) " + wstr2 + L" 에게 <<<<크리티컬>>>> " + to_wstring(damage) + L" 데미지를 입힘");
		TarGet->SetHp(tarGetHp - damage);
	}
	else
	{
		SkillMessage.push_back(wstr + L"이(가) " + wstr2 + L" 에게 " + to_wstring(damage) + L" 데미지를 입힘");
		TarGet->SetHp(tarGetHp - damage);
	}
	skillTextBuffer = SkillMessage;
	return SkillMessage;
}

