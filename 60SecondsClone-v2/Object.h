#pragma once

#include <Windows.h>
#include "Sprite.h"
#include "GameEvents.h"

#define BLACK		0
#define RED			FOREGROUND_RED
#define GREEN		FOREGROUND_GREEN
#define BLUE		FOREGROUND_BLUE
#define CYAN		(FOREGROUND_GREEN | FOREGROUND_BLUE)
#define YELLOW		(FOREGROUND_GREEN | FOREGROUND_RED)
#define MAGENTA		(FOREGROUND_RED | FOREGROUND_BLUE)
#define WHITE		(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

class Console;
class Character;
class Item;

#ifndef OBJECT_H
#define OBJECT_H

enum class Types : unsigned int {
	CHARACTER,
	ITEM,
	GAME_EVENT,
	DEFAULT
};

union Rect {
	struct {
		COORD position;
		COORD dimensions;
	};

	struct {
		SHORT x, y, w, h;
	};

	operator SMALL_RECT() {
		return SMALL_RECT{
			x, y,
			x + w, y + h
		};
	}
};

class Object {

	friend Console;

public:

	Object();
	Object(const Sprite& sprite);
	Object(const GameEvent& GE);
	Object(const string message, const SHORT colour = WHITE);

	virtual ~Object() = default;

	bool operator==(const Object& obj) const;
	bool operator!=(const Object& obj) const;
	bool operator>(const Object& obj) const;
	bool operator<(const Object& obj) const;

	void addTo(const Console& console);

	COORD getDimensions();
	
	COORD getPosition();
	void setPosition(const COORD position);
	void setPosition(const int x, const int y);
	void setPositionBy(const COORD position);
	void setPositionBy(const int x, const int y);

	Rect getRegion();
	int getInvSize();
	Types getType();
	
	bool hitReg(const Console& console, const COORD& translate = { 0, 0 });
	bool hitReg(const Console&, const int& x, const int& y);

	static bool checkCollision(Object obj1, Object obj2);

protected:

	Rect region;
	Types type;
	Sprite sprite;
	GameEvent GE;

	static int idCount;
	int id;
	int inventorySize;

private:

	Sprite textToSprite(const string msg, const SHORT colour);

};

#endif