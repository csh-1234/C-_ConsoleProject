#pragma once
#include "Skill.h"
#include "Enums.h"
class Creature;

class Heal : public Skill
{
public:
	Heal() : Skill()
	{
		_skillLevel = 1;
		_skillName = "��";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "ġ�� ������ ����� �������� ü���� ([ 10 X [��ų����])��ŭ ȸ���Ѵ�.";
	}
	~Heal();

	vector<wstring> ActiveSkillCast(Creature* Caster, Creature* Target);


};