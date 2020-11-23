#include "Object.h"
#include "Console.h"

int Object::idCount = 0;

Object::Object() {}
Object::Object(const string msg, const SHORT colour) : Object(textToSprite(msg, colour)) {}

bool Object::operator==(const Object& obj) const { return id == obj.id; }
bool Object::operator!=(const Object& obj) const { return id != obj.id; }

bool Object::operator>(const Object& obj) const { return id > obj.id; }
bool Object::operator<(const Object& obj) const { return id < obj.id; }


Object::Object(const Sprite& sprite) : sprite(sprite), id(idCount++) {
	region.position = COORD{ 1, 1 };
	region.dimensions = sprite.dimensions;
	GE.dimensions = COORD{ 0, 0 };

	type = Types::DEFAULT;
}

Object::Object(const GameEvent &GE) : GE(GE), id(0) {
	region.position = COORD{ 1, 1 };
	region.dimensions = GE.dimensions;
	sprite.dimensions = COORD{ 0, 0 };

	type = Types::GAME_EVENT;
}

void Object::addTo(const Console& console) {
	const int start = console._dimensions.X * region.y + region.x;
	int current;

	if (type == Types::GAME_EVENT) {
		for (unsigned int i = 0; i < GE.dimensions.Y; i++) {
			current = start + i * console._dimensions.X;
			memcpy(console._renderBuffer + current, GE.renderBuffer + i * GE.dimensions.X, GE.dimensions.X * sizeof(CHAR_INFO));
		}
	}
	else {
		for (unsigned int i = 0; i < sprite.dimensions.Y; i++) {
			current = start + i * console._dimensions.X;
			memcpy(console._renderBuffer + current, sprite.renderBuffer + i * sprite.dimensions.X, sprite.dimensions.X * sizeof(CHAR_INFO));
		}
	}
}

void Object::setPosition(const COORD position) {
	region.x = position.X;
	region.y = position.Y;
}

void Object::setPosition(const int x, const int y) {
	setPosition(COORD{ (SHORT)x, (SHORT)y });
}

void Object::setPositionBy(const COORD position) {
	region.x += position.X;
	region.y += position.Y;
}

void Object::setPositionBy(const int x, const int y) { setPositionBy(COORD{ (SHORT)x, (SHORT)y }); }

Rect Object::getRegion() { return region; }

int Object::getInvSize() { return inventorySize; }
Types Object::getType() { return type; }

bool Object::hitReg(const Console& console, const COORD& translate) {
	int consoleStart = (region.y + translate.Y) * console._dimensions.X + (region.x + translate.X);
	
	for (unsigned int i = 0; i < region.h; i++) {
		for (unsigned int j = 0; j < region.w; j++) {
			char consoleChar = console._renderBuffer[consoleStart + i * console._dimensions.X + j].Char.AsciiChar;
			char objectChar = sprite.renderBuffer[i * region.w + j].Char.AsciiChar;

			if (objectChar != ' ' && consoleChar != console._clearChar) return true;
		}
	}
	
	return false;
}

bool Object::hitReg(const Console& console, const int& x, const int& y) { return hitReg(console, COORD{ (SHORT)x, (SHORT)y }); }

bool Object::checkCollision(Object obj1, Object obj2) {
	bool AABBcheck = true;

	SMALL_RECT AABB1 = { obj1.getPosition().X, obj1.getPosition().Y,
						   obj1.getPosition().X + obj1.getDimensions().X, obj1.getPosition().Y + obj1.getDimensions().Y };
	SMALL_RECT AABB2 = { obj2.getPosition().X, obj2.getPosition().Y,
						 obj2.getPosition().X + obj2.getDimensions().X, obj2.getPosition().Y + obj2.getDimensions().Y };

	COORD min1 = { AABB1.Left, AABB1.Top };
	COORD max1 = { AABB1.Right, AABB1.Bottom };

	COORD min2 = { AABB2.Left, AABB2.Top };
	COORD max2 = { AABB2.Right, AABB2.Bottom };

	if (min1.X > max2.X || max1.X < min2.X) AABBcheck = false;
	if (min1.Y > max2.Y || max1.Y < min2.Y) AABBcheck = false;

	if (AABBcheck) {
		for (unsigned int h = 0; h < obj1.region.h; h++) {
		for (unsigned int i = 0; i < obj1.region.w; i++) {
		for (unsigned int j = 0; j < obj2.region.w; j++) {
		for (unsigned int k = 0; k < obj2.region.w; k++) {
			char obj1Char = obj1.sprite.renderBuffer[h * obj1.region.w + i].Char.AsciiChar;
			char obj2Char = obj2.sprite.renderBuffer[j * obj2.region.w + k].Char.AsciiChar;

			if (obj1Char != ' ' && obj2Char != ' ') return true;
		}
		}
		}
		}
	}

	return false;
}

COORD Object::getPosition() { return region.position; }
COORD Object::getDimensions() { return region.dimensions; }

Sprite Object::textToSprite(const string msg, const SHORT colour) {
	string temp = "";
	CHAR_INFO* text;

	int textWidth = 0, textHeight = 0;
	std::vector<string> contents;

	for (unsigned int i = 0; i < msg.length(); i++) {
		if (msg[i] != '\n')	temp += msg[i];
		else {
			contents.push_back(temp);
			temp = "";
		}
	}
	contents.push_back(temp);

	for (unsigned int i = 0; i < contents.size(); i++)
		if (textWidth < contents[i].length()) textWidth = contents[i].size();
	textHeight = (int)contents.size();

	text = new CHAR_INFO[textWidth * textHeight];
	for (unsigned int i = 0; i < textHeight; i++) {
		for (unsigned int j = 0; j < textWidth; j++) {
			int index = i * textWidth + j;

			if (contents[i].length() < j) text[index].Char.AsciiChar = ' ';
			else text[index].Char.AsciiChar = contents[i][j];
			text[index].Attributes = colour;
		}
	}

	return Sprite(textWidth, textHeight, text);
}


