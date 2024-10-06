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
	int P_hpRecoverAmount;  // hp 회복략
	int P_mpRecoverAmount;  // mp 회복량
	vector<wstring > potionTextBuffer;
};

class HalthIPotion : public IPotion
{
public:
	HalthIPotion() : IPotion()
	{
		_itemName = "체력 포션";			// 아이템 이름
		_itemType = ItemType::Potion;	// 아이템 분류
		_itemQuantity = 1;					// 아이템 개수
		_itemPrice = 100;					// 아이템 가격

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
		_itemName = "마나 포션";			// 아이템 이름
		_itemType = ItemType::Potion;	// 아이템 분류
		_itemQuantity = 1;					// 아이템 개수
		_itemPrice = 300;					// 아이템 가격

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
		_itemName = "엘릭서";			// 아이템 이름
		_itemType = ItemType::Potion;	// 아이템 분류
		_itemQuantity = 1;					// 아이템 개수
		_itemPrice = 5000;					// 아이템 가격

		P_hpRecoverAmount = 100000;
		P_mpRecoverAmount = 100000;
	}

	~Elixir() {}
	vector<wstring> UsePotion(Creature* Caster);
};