#include "Creature.h"
#include "Skill.h"
#include "IPotion.h"
#include "Enums.h"
using namespace std;

Creature::Creature(int unitType) :_name(""), _unitType(unitType), _maxHp(0), _hp(0), _maxMp(0), _mp(0), _atk(0), _def(0), _criRate(0),
_criDamage(0), _money(0), _posX(1), _posY(1), _exp(0), _level(0) {}
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

int Creature::GetExp() const
{
	return _exp;
}

void Creature::SetExp(int inputExp)
{
	_exp += inputExp;
}

int Creature::GetLevel() const
{
	return _level;
}

void Creature::SetLevel(int inputLevel)
{
	_level = inputLevel;
}

void Creature::addActiveSkill(Skill* skill)
{
	_ActiveSkillList.push_back(skill);
}
void Creature::addPasiveSkill(Skill* skill)
{
	_PassiveSkillList.push_back(skill);
}
vector<Skill*> Creature::getActiveSkillList()
{
	return _ActiveSkillList;
}
void Creature::addPotion(IPotion* potion, int count)
{
	if (_PotionList.size() != 0)
	{
		for (size_t i = 0; i < _PotionList.size(); i++)
		{
			if (_PotionList[i] == potion)
			{
				potion->setItemQuantity(count);
				return;
			}
			else
			{
				_PotionList.push_back(potion);
				return;
			}
		}
	}
	else
	{
		_PotionList.push_back(potion);
	}

}
vector<IPotion*> Creature::getPotionlList()
{
	return _PotionList;
}
#pragma endregion

