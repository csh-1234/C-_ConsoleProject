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
		_skillName = "힐";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "치유 마법을 사용해 시전자의 체력을 ([ 10 X [스킬레벨])만큼 회복한다.";
	}
	~Heal();

	vector<wstring> ActiveSkillCast(Creature* Caster, Creature* Target);


};