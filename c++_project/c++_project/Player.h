#pragma once
#pragma once

#include <iostream>
#include <vector>
#include "Creature.h"
#include "Enums.h"
#include "Skill.h"
using namespace std;

class Player : public Creature
{
public:
	Player(string playerName);
	~Player();

	void useSkill(Creature* Caster, Creature* Target, int index)
	{
		if (index >= 0 && index < _ActiveSkillList.size())
		{
			if (_ActiveSkillList[index]->getSkillType() == SkillType::Active)
			{
				_ActiveSkillList[index]->ActiveSkillCast(Caster, Target);
			}
			else if (_ActiveSkillList[index]->getSkillType() == SkillType::Buff)
			{
				_ActiveSkillList[index]->BuffSkillCast(Caster);
			}
			//else // passive
			//{
			//	cout << "패시브 스킬은 자동으로 발동합니다." << endl;
			//}
		}
	}

};



