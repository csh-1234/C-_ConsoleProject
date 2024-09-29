#include "Creature.h"
#include <iostream>
using namespace std;

Creature::Creature(int unitType) :
	_name(""), _unitType(unitType), _maxHp(0), _hp(0), _maxMp(0), _mp(0), _atk(0), _def(0), _criRate(0),
	_criDamage(0), _avoidRate(0), _speed(0), _money(0), _posX(1), _posY(1) {}
Creature::~Creature() {}

#pragma region Property
string Creature::GetName() const
{
	return _name;
}
void Creature::SetName(string inputName)
{
	_name = inputName;
}
int Creature::GetHp() const
{
	return _hp;
}
void Creature::SetHp(int inputHp)
{
	_hp = inputHp;
}
int Creature::GetMaxHp() const
{
	return _maxHp;
}
void Creature::SetMaxHp(int inputMaxHp)
{
	_maxHp = inputMaxHp;
}
int Creature::GetMaxMp() const
{
	return _maxMp;
}
void Creature::SetMaxMp(int inputMaxMp)
{
	_maxMp = inputMaxMp;
}
int Creature::GetMp() const
{
	return _mp;
}
void Creature::SetMp(int inputMp)
{
	_mp = inputMp;
}
int Creature::GetAtk() const
{
	return _atk;
}
void Creature::SetAtk(int inputAtk)
{
	_atk = inputAtk;
}
int Creature::GetDef() const
{
	return _def;
}
void Creature::SetDef(int inputDef)
{
	_def = inputDef;
}
float Creature::GetCriRate() const
{
	return _criRate;
}
void Creature::SetCriRate(int inputCriRate)
{
	_criRate = inputCriRate;
}
int Creature::GetCriDamage() const
{
	return _criDamage;
}
void Creature::SetCriDamage(int inputCriDamage)
{
	_criDamage = inputCriDamage;
}
int Creature::GetAvoidRate() const
{
	return _avoidRate;
}
void Creature::SetAvoidRate(int inputAvoidRate)
{
	_avoidRate = inputAvoidRate;
}
int Creature::GetSpeed() const
{
	return _speed;
}
void Creature::SetSpeed(int inputSpeed)
{
	_speed = inputSpeed;
}
int Creature::GetMoney() const
{
	return _money;
}
void Creature::SetMoney(int inputMoney)
{
	_money = inputMoney;
}
int Creature::GetPosX() const
{
	return _posX;
}
void Creature::SetPosX(int inputPosX)
{
	_posX = inputPosX;
}
int Creature::GetPosY() const
{
	return _posY;
}
void Creature::SetPosY(int inputPosY)
{
	_posY = inputPosY;
}

#pragma endregion

void Creature::PrintUnit()
{
	cout << "==========유닛 정보==========" << endl;
	cout << "이름 : " << _name << endl;
	cout << "체력/최대체력 : " << _hp << " / " << _maxHp << endl;
	cout << "마나/최대마나 : " << _mp << " / " << _maxMp << endl;
	cout << "공격력 : " << _atk << endl;
	cout << "방어력 : " << _def << endl;
	cout << "크리티컬 확률 : " << _criRate << "" << endl;
	cout << "크리티컬 데미지 : " << _criDamage << endl;
	cout << "회피율 : " << _avoidRate << "%" << endl;
	cout << "속도 : " << _speed << endl;
	cout << "소지금 : " << _money << "골드" << endl;
	cout << "============================" << endl;
}