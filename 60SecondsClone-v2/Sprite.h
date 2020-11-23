#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

typedef std::string string;
typedef std::ifstream fStream;

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
	Sprite();
	Sprite(COORD dimensions, CHAR_INFO* buffer);
	Sprite(int width, int height, CHAR_INFO* buffer);

	COORD dimensions;
	CHAR_INFO* renderBuffer;
};

enum Sprites : unsigned int {
	NEW_GAME_BUTTON, NEW_GAME_SELECT,
	INSTRUCTIONS_BUTTON, INSTRUCTIONS_SELECT,
	EXIT_BUTTON, EXIT_SELECT,

	DANIEL, EDWARD, DELENTIA, TAVIS,

	SOUP, WATER, MEDKIT,
	RADIO, MAP, PISTOL,	RAT_POISON, AXE,
	
	TITLE_SCREEN, DEV_LOGO, 
	COPYRIGHT, BORDER,

	INSTRUCTIONS,
	LEVEL, SHELTER_HATCH,
	DAY_TITLE, NOTEBOOK,
	NOTEBOOK_TEXT_STATUS,
	NOTEBOOK_TEXT_RATION,
	GAME_OVER_WIN, GAME_OVER_LOSE,

	NUM_SPRITES
};

class SpriteCache {
public:
	static void initialize();
	static const Sprite& get(Sprites sprite);

private:
	static Sprite* _spriteCache;
	static Sprite load(const char* filePath);
};

#endif