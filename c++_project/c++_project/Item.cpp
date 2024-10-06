#include "Item.h"

Item::Item() : _itemName(""), _itemType(0), _itemQuantity(0), _itemPrice(0) {}

Item::~Item()
{
}

string Item::getItemName()
{
	return _itemName;
}

int Item::getItemType()
{
	return _itemType;
}

int Item::getItemQuantity()
{
	return _itemQuantity;
}

int Item::getItemPrice()
{
	return _itemPrice;
}

void Item::setItemQuantity()
{
	_itemQuantity--;
}

void Item::setItemQuantity(int quantity)
{
	_itemQuantity += quantity;
}
