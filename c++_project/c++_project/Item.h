#pragma once
#include<iostream>
#include <vector>
using namespace std;
class Creature;

class Item
{
public:
	Item();
	~Item();

	string getItemName();
	int getItemType();
	int getItemQuantity();
	int getItemPrice();
	void setItemQuantity();
	void setItemQuantity(int quantity);

	//virtual void UseItem(Creature* Caster) {};
protected:
	string _itemName;
	int _itemType;
	int _itemQuantity;
	int _itemPrice;
};