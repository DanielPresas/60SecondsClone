#include "Sprite.h"

#define BLACK			0
#define RED				FOREGROUND_RED
#define GREEN			FOREGROUND_GREEN
#define BLUE			FOREGROUND_BLUE
#define CYAN			(FOREGROUND_GREEN | FOREGROUND_BLUE)
#define YELLOW			(FOREGROUND_GREEN | FOREGROUND_RED)
#define MAGENTA			(FOREGROUND_RED | FOREGROUND_BLUE)
#define WHITE			(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#define RED_BACK		BACKGROUND_RED
#define GREEN_BACK		BACKGROUND_GREEN
#define BLUE_BACK		BACKGROUND_BLUE
#define CYAN_BACK		(BACKGROUND_GREEN | BACKGROUND_BLUE)
#define YELLOW_BACK		(BACKGROUND_GREEN | BACKGROUND_RED)
#define MAGENTA_BACK	(BACKGROUND_RED | BACKGROUND_BLUE)
#define WHITE_BACK		(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)

#define INTENSIFY		FOREGROUND_INTENSITY
#define INTENSIFY_BACK	BACKGROUND_INTENSITY

Sprite::Sprite() {}
Sprite::Sprite(COORD dimensions, CHAR_INFO* buffer) : dimensions(dimensions), renderBuffer(buffer) {}
Sprite::Sprite(int width, int height, CHAR_INFO* buffer) : Sprite(COORD{ (SHORT)width, (SHORT)height }, buffer) {}

Sprite* SpriteCache::_spriteCache;

void SpriteCache::initialize() {
	_spriteCache = new Sprite[Sprites::NUM_SPRITES];

	_spriteCache[Sprites::NEW_GAME_BUTTON]		= load("sprites/buttons/new-game-button");
	_spriteCache[Sprites::INSTRUCTIONS_BUTTON]	= load("sprites/buttons/instructions-button");
	_spriteCache[Sprites::EXIT_BUTTON]			= load("sprites/buttons/exit-button");
	_spriteCache[Sprites::NEW_GAME_SELECT]		= load("sprites/buttons/new-game-button-selected");
	_spriteCache[Sprites::INSTRUCTIONS_SELECT]	= load("sprites/buttons/instructions-button-selected");
	_spriteCache[Sprites::EXIT_SELECT]			= load("sprites/buttons/exit-button-selected");

	_spriteCache[Sprites::DANIEL]	= load("sprites/characters/daniel");
	_spriteCache[Sprites::EDWARD]	= load("sprites/characters/edward");
	_spriteCache[Sprites::DELENTIA] = load("sprites/characters/delentia");
	_spriteCache[Sprites::TAVIS]	= load("sprites/characters/tavis");

	_spriteCache[Sprites::SOUP]			= load("sprites/items/soup");
	_spriteCache[Sprites::WATER]		= load("sprites/items/water");
	_spriteCache[Sprites::MEDKIT]		= load("sprites/items/medkit");
	_spriteCache[Sprites::RADIO]		= load("sprites/items/radio");
	_spriteCache[Sprites::MAP]			= load("sprites/items/map");
	_spriteCache[Sprites::PISTOL]		= load("sprites/items/pistol");
	_spriteCache[Sprites::RAT_POISON]	= load("sprites/items/rat-poison");
	_spriteCache[Sprites::AXE]			= load("sprites/items/axe");

	_spriteCache[Sprites::TITLE_SCREEN] = load("sprites/misc/title-screen");
	_spriteCache[Sprites::DEV_LOGO]		= load("sprites/misc/dev-logo");
	_spriteCache[Sprites::COPYRIGHT]	= load("sprites/misc/copyright");
	_spriteCache[Sprites::BORDER]		= load("sprites/misc/border");

	_spriteCache[Sprites::INSTRUCTIONS]		= load("sprites/visuals/instructions");
	_spriteCache[Sprites::LEVEL]			= load("sprites/visuals/level");
	_spriteCache[Sprites::SHELTER_HATCH]	= load("sprites/visuals/shelter-hatch");
	_spriteCache[Sprites::DAY_TITLE]		= load("sprites/visuals/day-title");
	_spriteCache[Sprites::NOTEBOOK]			= load("sprites/visuals/notebook");

	_spriteCache[Sprites::NOTEBOOK_TEXT_STATUS]	= load("sprites/visuals/notebook");
	_spriteCache[Sprites::NOTEBOOK_TEXT_RATION]	= load("sprites/visuals/notebook");

	_spriteCache[Sprites::GAME_OVER_LOSE] = load("sprites/visuals/game-over-lose");
	_spriteCache[Sprites::GAME_OVER_WIN]  = load("sprites/visuals/game-over-win");
}

const Sprite& SpriteCache::get(Sprites sprite) { return _spriteCache[sprite]; }

Sprite SpriteCache::load(const char* filePath) {
	string end = ".txt";
	string colourEnd = "-info.txt";

	string path = filePath + end;
	string infoPath = filePath + colourEnd;

	fStream file(path);
	fStream colourFile(infoPath);

	string line;
	std::vector<string> contents;
	std::vector<string> colourInfo;

	int spriteWidth = 0, spriteHeight = 0;

	while (std::getline(file, line)) {
		contents.push_back(line);
		if (line.length() > spriteWidth) spriteWidth = line.length();
	}
	spriteHeight = (int)contents.size();

	while (std::getline(colourFile, line)) {
		colourInfo.push_back(line);
	}

	CHAR_INFO* asciiSprite = new CHAR_INFO[spriteWidth * spriteHeight];
	for (unsigned int i = 0; i < spriteHeight; i++) {
		for (unsigned int j = 0; j < spriteWidth; j++) {
			int index = i * spriteWidth + j;

			if (contents[i].length() < j) {
				asciiSprite[index].Char.AsciiChar = 255;
				asciiSprite[index].Attributes = WHITE;
			}
			else {
				asciiSprite[index].Char.AsciiChar = contents[i][j];

				switch (colourInfo[i][j]) {
				case 'r':
					asciiSprite[index].Attributes = RED;
					break;
				case 'R':
					asciiSprite[index].Attributes = RED | INTENSIFY;
					break;
				case 'g':
					asciiSprite[index].Attributes = GREEN;
					break;
				case 'G':
					asciiSprite[index].Attributes = GREEN | INTENSIFY;
					break;
				case 'b':
					asciiSprite[index].Attributes = BLUE;
					break;
				case 'B':
					asciiSprite[index].Attributes = BLUE | INTENSIFY;
					break;
				case 'c':
					asciiSprite[index].Attributes = CYAN;
					break;
				case 'C':
					asciiSprite[index].Attributes = CYAN | INTENSIFY;
					break;
				case 'y':
					asciiSprite[index].Attributes = YELLOW;
					break;
				case 'Y':
					asciiSprite[index].Attributes = YELLOW | INTENSIFY;
					break;
				case 'm':
					asciiSprite[index].Attributes = MAGENTA;
					break;
				case 'M':
					asciiSprite[index].Attributes = MAGENTA | INTENSIFY;
					break;
				case 'k':
					asciiSprite[index].Attributes = BLACK | INTENSIFY;
					break;
				case 'K':
					asciiSprite[index].Attributes = BLACK | WHITE_BACK;
					break;
				default:
					asciiSprite[index].Attributes = WHITE;
					break;
				}

			}
		}
	}

	file.close();
	colourFile.close();
	return Sprite(spriteWidth, spriteHeight, asciiSprite);
}