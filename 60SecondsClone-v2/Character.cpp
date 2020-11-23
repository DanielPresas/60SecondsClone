#include "Character.h"
#include "Math.h"

std::vector<Character> Character::AllCharacters;

Character::Character(const Sprite& sprite, const int size, bool sick, bool hungry, bool thirsty) : Object(sprite),
	isSick(sick), isHungry(hungry), isThirsty(thirsty),
	sickDays(0), hungryDays(0), thirstyDays(0), fineDays(0) {

	inventorySize = size;
	type = Types::CHARACTER;
}

void Character::add(const Character& chr) { AllCharacters.push_back(chr); }
void Character::remove(const Character& chr) { AllCharacters.erase(std::find(AllCharacters.begin(), AllCharacters.end(), chr)); }

void Character::updateTo(Console& console) {
	int xStep = 1, yStep = 1, x = 0, y = 0;

	if (Input::isEvent(Events::W)) y -= yStep;
	if (Input::isEvent(Events::A)) x -= xStep;
	if (Input::isEvent(Events::S)) y += yStep;
	if (Input::isEvent(Events::D)) x += xStep;

	if (contains(console.getBoundingBox(), translatedObject((SMALL_RECT)region, x, y)) && !hitReg(console, x, y)) setPositionBy(x, y);
	
	addTo(console);
}