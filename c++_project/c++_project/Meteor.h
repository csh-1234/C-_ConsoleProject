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
		_skillName = "메테오";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "거대한 화염구를 날려 적에게 ([공격력] X 100 X [스킬레벨])피해를 입힌다.";
	}
	~Meteor();

	vector<wstring> ActiveSkillCast(Creature* Caster, Creature* Target);


};