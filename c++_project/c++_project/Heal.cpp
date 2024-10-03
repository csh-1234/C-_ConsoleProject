#include "Heal.h"
#include "Creature.h"
#include <string>
#pragma warning(disable:4996)
Heal::~Heal()
{
}

vector<wstring> Heal::ActiveSkillCast(Creature* Caster, Creature* TarGet)
{
	vector<wstring> SkillMessage;
	string casterName = Caster->GetName();


	if (Caster->GetMaxHp() < Caster->GetHp() + _skillLevel * 10)
	{
		Caster->SetHp(Caster->GetMaxHp());
	}
	else
	{
		Caster->SetHp(Caster->GetHp() + _skillLevel * 10);
	}


	Caster->SetMp(Caster->GetMp() - _skillCost);
	wstring wstr(casterName.size(), L'\0');
	std::mbstowcs(&wstr[0], casterName.c_str(), casterName.size());

	SkillMessage.push_back(wstr + L"��(��)" + L" ��ų [ �� ] ����!");
	SkillMessage.push_back(wstr + L"��(��) ü��" + to_wstring(_skillLevel * 10) + L"��ŭ ȸ�� ");

	skillTextBuffer = SkillMessage;

	return SkillMessage;
}

