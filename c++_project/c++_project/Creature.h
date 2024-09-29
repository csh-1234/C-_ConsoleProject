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
	string _name;		// �̸�
	int _unitType;		// ���� ����(�÷��̾�, ����)
	int _maxHp;			// �ִ� ü��
	int _hp;			// ���� ü��
	int _maxMp;			// �ִ� ����
	int _mp;			// �⺻ ����
	int _atk;			// �⺻ ���ݷ�
	int _def;			// �⺻ ����
	int _criRate;		// �⺻ ũ��Ƽ�� Ȯ��
	float _criDamage;	// �⺻ ũ��Ƽ�� ������
	int _avoidRate;		// �⺻ ȸ����
	int _speed;			// �⺻ �ӵ�
	int _money;			// ������
	int _posX;
	int _posY;
	/*vector<Skill*> _ActiveSkillList;
	vector<Skill*> _PassiveSkillList;*/
	//vector<Item*> _inventory;
};