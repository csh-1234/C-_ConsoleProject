#include "Skill.h"

Skill::Skill() :_skillLevel(0), _skillName(""), _skillType(0), _skillCost(0), _skillInfo(""), _isActivate(false) { }
Skill::~Skill(){}
string Skill::getSkillName()
{
	return _skillName;
}
int Skill::getSkillType()
{
	return _skillType;
}
int Skill::getSkillCost()
{
	return _skillCost;
}
bool Skill::getIsActivate()
{
	return _isActivate;
}
