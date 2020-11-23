#pragma once

#include "Object.h"
#include "Input.h"
#include "Console.h"

#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public Object {
public:
	Character(const Sprite& Sprite, const int size = 2,
			  bool sick = false,
			  bool hungry = false,
			  bool thirsty = false);

	bool isSick, isHungry, isThirsty;
	bool hasFood, hasWater, hasMed;
	int sickDays, hungryDays, thirstyDays, fineDays;

	static std::vector<Character> AllCharacters;

	static void add(const Character& chr);
	static void remove(const Character& chr);

	void updateTo(Console& console);
};

#endif