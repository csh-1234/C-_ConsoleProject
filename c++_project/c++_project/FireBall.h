#pragma once
#include "Skill.h"
#include "Enums.h"
class Creature;

class FireBall : public Skill
{
public:
	FireBall() : Skill()
	{
		_skillLevel = 1;
		_skillName = "파이어볼";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "화염구를 날려 적에게 ([공격력] X 2 X [스킬레벨])피해를 입힌다.";
	}
	~FireBall();

	vector<wstring> ActiveSkillCast(Creature* Caster, Creature* Target);


};