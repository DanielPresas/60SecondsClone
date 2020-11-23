#include "Item.h"

std::vector<Item> Item::ItemCollection;

Item::Item(const Sprite &Sprite, const int size) : Object(Sprite) {
	inventorySize = size;
	type = Types::ITEM;
}

void Item::add(const Item& item) { ItemCollection.push_back(item); }
void Item::remove(const Item& item) { ItemCollection.erase(std::find(ItemCollection.begin(), ItemCollection.end(), item)); }