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
	int getSkillType();
	int getSkillCost();
	bool getIsActivate();
#pragma endregion
	
protected:
	int _skillLevel;
	string _skillName;
	int _skillType;
	int _skillCost; //���� �Һ�
	string _skillInfo;
	bool _isActivate; //�ϴ��� �нú� ��ų���� ����
	vector<wstring> skillTextBuffer;
};

