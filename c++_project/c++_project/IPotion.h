#pragma once
#include "Item.h"
#include "Enums.h"

class Creature;
class IPotion : public Item
{
public:
	IPotion() :Item(), P_hpRecoverAmount(0), P_mpRecoverAmount(0) {}
	virtual ~IPotion() {}
	virtual std::vector<wstring> UsePotion(Creature* Caster) { return potionTextBuffer; }

protected:
	int P_hpRecoverAmount;  // hp ȸ����
	int P_mpRecoverAmount;  // mp ȸ����
	vector<wstring > potionTextBuffer;
};

class HalthIPotion : public IPotion
{
public:
	HalthIPotion() : IPotion()
	{
		_itemName = "ü�� ����";			// ������ �̸�
		_itemType = ItemType::Potion;	// ������ �з�
		_itemQuantity = 1;					// ������ ����
		_itemPrice = 100;					// ������ ����

		P_hpRecoverAmount = 100;
	}
	~HalthIPotion() {}
	
	vector<wstring> UsePotion(Creature* Caster);
	
};
class ManaIPotion : public IPotion
{
public:
	ManaIPotion() : IPotion()
	{
		_itemName = "���� ����";			// ������ �̸�
		_itemType = ItemType::Potion;	// ������ �з�
		_itemQuantity = 1;					// ������ ����
		_itemPrice = 300;					// ������ ����

		P_mpRecoverAmount = 100;
	}
	~ManaIPotion() {}

	vector<wstring> UsePotion(Creature* Caster);
};

class Elixir : public IPotion
{
public:
	Elixir() : IPotion()
	{
		_itemName = "������";			// ������ �̸�
		_itemType = ItemType::Potion;	// ������ �з�
		_itemQuantity = 1;					// ������ ����
		_itemPrice = 5000;					// ������ ����

		P_hpRecoverAmount = 100000;
		P_mpRecoverAmount = 100000;
	}

	~Elixir() {}
	vector<wstring> UsePotion(Creature* Caster);
};