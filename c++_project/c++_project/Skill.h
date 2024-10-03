#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Creature;
class Skill
{
public:
	Skill();
	~Skill();

	virtual std::vector<wstring> ActiveSkillCast(Creature* Attacker, Creature* Defender) { return skillTextBuffer; }
	virtual void PassiveSkillCast(Creature* Caster) {};
	virtual void BuffSkillCast(Creature* Caster) {};
#pragma region Property
	string getSkillName();
	int getSkillLevel();
	int getSkillType();
	int getSkillCost();
	string gertSkillInfo();
	bool getIsActivate();
	void setSkillLevel(int inputLevel);
#pragma endregion

protected:
	int _skillLevel;
	string _skillName;
	int _skillType;
	int _skillCost; //마나 소비량
	string _skillInfo;
	bool _isActivate; //일단은 패시브 스킬에만 적용
	vector<wstring> skillTextBuffer;
};

