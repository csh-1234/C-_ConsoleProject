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
		_skillName = "���̾";
		_skillType = static_cast<int>(SkillType::Active);
		_skillCost = 5;
		_skillInfo = "ȭ������ ���� ������ ([���ݷ�] X 2 X [��ų����])���ظ� ������.";
	}
	~FireBall();

	vector<wstring> ActiveSkillCast(Creature* Caster, Creature* Target);


};