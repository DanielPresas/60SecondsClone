#pragma once

#include "Object.h"
#include <Windows.h>
#include <cwchar>

#ifndef CONSOLE_H
#define CONSOLE_H

class Console {
	friend bool Object::hitReg(const Console&, const COORD&);
	friend bool Object::hitReg(const Console&, const int&, const int&);
	friend void Object::addTo(const Console&);

public:
	Console(int size = 16);
	~Console();

	const COORD& getDimensions() const;
	DWORD getSize() const;
	SMALL_RECT getBoundingBox() const;

	void setFontSize(int size);
	COORD getFontSize();

	void render();
	void clearBuffer(char clearChar = ' ', WORD clearColour = 0);
	void showDefaultBuffer();

private:
	HANDLE _hIn, _hOut;
	
	SMALL_RECT _window;
	SMALL_RECT _boundingBox;
	
	const COORD _origin;
	COORD _dimensions;

	CONSOLE_FONT_INFOEX _fontInfo;
	COORD _fontSize;

	HANDLE _buffers[2];
	CHAR_INFO* _renderBuffer;
	DWORD _bufferSize;
	int _frontBufferIndex, _backBufferIndex;
	
	char _clearChar;

	void clearScreen(char clearChar = '*', WORD clearColour = 0x0004);

	void showFrontBuffer();
	void showBackBuffer();
	
	HANDLE& getFrontBuffer();
	HANDLE& getBackBuffer();
};

#endif