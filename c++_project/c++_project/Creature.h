#pragma once
#include <iostream>
#include <vector>
using namespace std;


class Creature
{
public:
	Creature(int unitType);
	virtual ~Creature();
#pragma region Property
	string GetName()const;
	void SetName(string inputName);
	int GetHp()const;
	void SetHp(int inputHp);
	int GetMaxHp()const;
	void SetMaxHp(int inputMaxHp);
	int GetMaxMp()const;
	void SetMaxMp(int inputMaxMp);
	int GetMp()const;
	void SetMp(int inputMp);
	int GetAtk()const;
	void SetAtk(int inputAtk);
	int GetDef()const;
	void SetDef(int inputDef);
	float GetCriRate()const;
	void SetCriRate(int inputCriRate);
	int GetCriDamage()const;
	void SetCriDamage(int inputCriDamage);
	int GetAvoidRate()const;
	void SetAvoidRate(int inputAvoidRate);
	int GetSpeed()const;
	void SetSpeed(int inputSpeed);
	int GetMoney()const;
	void SetMoney(int inputMoney);
	int GetPosX()const;
	void SetPosX(int inputPosX);
	int GetPosY()const;
	void SetPosY(int inputPosY);
	void PrintUnit();
#pragma endregion
#pragma region CommonMethod
	//void addActiveSkill(Skill* skill)
	//{
	//	_ActiveSkillList.push_back(skill);
	//}
	//void addPasiveSkill(Skill* skill)
	//{
	//	_PassiveSkillList.push_back(skill);
	//}
#pragma endregion

protected:
	string _name;		// 이름
	int _unitType;		// 유닛 종류(플레이어, 몬스터)
	int _maxHp;			// 최대 체력
	int _hp;			// 기초 체력
	int _maxMp;			// 최대 마나
	int _mp;			// 기본 마나
	int _atk;			// 기본 공격력
	int _def;			// 기본 방어력
	int _criRate;		// 기본 크리티컬 확률
	float _criDamage;	// 기본 크리티컬 데미지
	int _avoidRate;		// 기본 회피율
	int _speed;			// 기본 속도
	int _money;			// 소지금
	int _posX;
	int _posY;
	/*vector<Skill*> _ActiveSkillList;
	vector<Skill*> _PassiveSkillList;*/
	//vector<Item*> _inventory;
};