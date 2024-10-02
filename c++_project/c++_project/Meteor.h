#pragma once
#include "Skill.h"
#include "Enums.h"
class Creature;

class Meteor : public Skill
{
public:
	Meteor() : Skill()
	{
		_skillLevel = 1;
		_skillName = "���׿�";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "�Ŵ��� ȭ������ ���� ������ ([���ݷ�] X 100 X [��ų����])���ظ� ������.";
	}
	~Meteor();

	vector<wstring> ActiveSkillCast(Creature* Caster, Creature* Target);


};