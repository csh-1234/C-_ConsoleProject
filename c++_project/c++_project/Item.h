#pragma once
#include<iostream>
#include <vector>
using namespace std;
class Creature;

class Item
{
public:
	Item() : _itemName(""), _itemType(0), _itemQuantity(0), _itemPrice(0) {}
	~Item() {}

	

	string getItemName()
	{
		return _itemName;
	}
	int getItemType()
	{
		return _itemType;
	}
	int getItemQuantity()
	{
		return _itemQuantity;
	}
	void setItemQuantity()
	{
		_itemQuantity--;
	}
	void setItemQuantity(int quantity)
	{
		_itemQuantity += quantity;
	}
	//virtual void UseItem(Creature* Caster) {};

protected:
	string _itemName;
	int _itemType;
	int _itemQuantity;
	int _itemPrice;

};