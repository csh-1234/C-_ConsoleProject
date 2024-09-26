#include "Skill.h"

Skill::Skill() :_skillLevel(0), _skillName(""), _skillType(0), _skillCost(0), _skillInfo(""), _isActivate(false) { }

Skill::~Skill()
{
}

#pragma region property
string Skill::GetSkillName()
{
	return string();
}
int Skill::GetSkillType()
{
	return _skillType;
}
int Skill::GetSkillCost()
{
	return _skillCost;
}
bool Skill::GetIsActivate()
{
	return _isActivate;
}
#pragma endregion

