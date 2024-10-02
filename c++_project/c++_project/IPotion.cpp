#include "IPotion.h"
#include "Creature.h"
#include <string>
#pragma warning(disable:4996)
vector<wstring> HalthIPotion::UsePotion(Creature* Caster)
{
	vector<wstring> PotionMessage;

	string casterName = Caster->GetName();
	wstring wstr(casterName.size(), L'\0');
	std::mbstowcs(&wstr[0], casterName.c_str(), casterName.size());
	PotionMessage.push_back(wstr + L"��(��)" + L" ���� [ ü������ ] ���!");
	if (Caster->GetHp() + P_hpRecoverAmount > Caster->GetMaxHp())
	{
		Caster->SetHp(Caster->GetMaxHp());
	}
	else
	{
		Caster->SetHp(Caster->GetHp() + P_hpRecoverAmount);
	}
	PotionMessage.push_back(wstr + L"��(��) ü��" + to_wstring(100) + L"��ŭ ȸ�� ");
	
	potionTextBuffer = PotionMessage;
	return potionTextBuffer;
}

vector<wstring> ManaIPotion::UsePotion(Creature* Caster)
{
	vector<wstring> PotionMessage;

	string casterName = Caster->GetName();
	wstring wstr(casterName.size(), L'\0');
	std::mbstowcs(&wstr[0], casterName.c_str(), casterName.size());

	PotionMessage.push_back(wstr + L"��(��)" + L" ���� [ �������� ] ���!");
	if (Caster->GetMp() + P_hpRecoverAmount > Caster->GetMaxMp())
	{
		Caster->SetMp(Caster->GetMaxMp());
	}
	else
	{
		Caster->SetMp(Caster->GetMp() + P_hpRecoverAmount);
	}
	PotionMessage.push_back(wstr + L"��(��) ����" + to_wstring(100) + L"��ŭ ȸ�� ");

	potionTextBuffer = PotionMessage;
	return potionTextBuffer;
}

vector<wstring> Elixir::UsePotion(Creature* Caster)
{
	vector<wstring> PotionMessage;

	string casterName = Caster->GetName();
	wstring wstr(casterName.size(), L'\0');
	std::mbstowcs(&wstr[0], casterName.c_str(), casterName.size());

	PotionMessage.push_back(wstr + L"��(��)" + L" ���� [ ������ ] ���!");
	Caster->SetHp(Caster->GetMaxHp());
	Caster->SetMp(Caster->GetMaxMp());
	PotionMessage.push_back(wstr + L"��(��) ü��, ���� ��� ȸ�� ");

	potionTextBuffer = PotionMessage;
	return potionTextBuffer;
}
