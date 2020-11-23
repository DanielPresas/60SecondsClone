#pragma once
#include "Object.h"
#include "Console.h"


#ifndef ITEM_H
#define ITEM_H

class Item : public Object {
public:
	Item(const Sprite& Sprite, const int size = 1);

	static std::vector<Item> ItemCollection;

	static void add(const Item& item);
	static void remove(const Item& item);
};

#endif