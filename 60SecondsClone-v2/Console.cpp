#include "Console.h"

Console::Console(int size) : _origin({ 0, 0 }), _frontBufferIndex(0), _backBufferIndex(1), _renderBuffer(nullptr) {
	_hIn = GetStdHandle(STD_INPUT_HANDLE);
	_hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	getFrontBuffer() = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	getBackBuffer() = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	
	// Front buffer
	showFrontBuffer();
	SetConsoleDisplayMode(getFrontBuffer(), CONSOLE_FULLSCREEN, nullptr);

	_fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(getFrontBuffer(), true, &_fontInfo);
	_fontInfo.nFont = 0;
	
	_fontInfo.FontFamily = FF_DONTCARE;
	_fontInfo.FontWeight = FW_NORMAL;

	wcscpy_s(_fontInfo.FaceName, L"Terminal");

	_fontInfo.dwFontSize.X = 6;
	_fontInfo.dwFontSize.Y = 8;
	SetCurrentConsoleFontEx(getFrontBuffer(), true, &_fontInfo);

	// Back buffer
	showBackBuffer();
	SetConsoleDisplayMode(getBackBuffer(), CONSOLE_FULLSCREEN, nullptr);	
	SetCurrentConsoleFontEx(getBackBuffer(), true, &_fontInfo);

	showFrontBuffer();
	_fontSize = GetConsoleFontSize(getFrontBuffer(), _fontInfo.nFont);

	_dimensions = GetLargestConsoleWindowSize(getFrontBuffer());
	_window = SMALL_RECT{ 0, 0, _dimensions.X - 1, _dimensions.Y - 1 };
	_boundingBox = SMALL_RECT{ 0, 0, _dimensions.X, _dimensions.Y };

	SetConsoleScreenBufferSize(getFrontBuffer(), _dimensions);
	SetConsoleScreenBufferSize(getBackBuffer(), _dimensions);
	SetConsoleWindowInfo(getFrontBuffer(), true, &_window);
	SetConsoleWindowInfo(getBackBuffer(), true, &_window);

	_bufferSize = _dimensions.X * _dimensions.Y;
	_renderBuffer = new CHAR_INFO[_bufferSize];
	clearBuffer();

	SetConsoleMode(_hIn, ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS);
}

Console::~Console() { delete[] _renderBuffer; }

void Console::render() {
	showFrontBuffer();
	WriteConsoleOutputA(getBackBuffer(), _renderBuffer, _dimensions, _origin, &_window);
	showBackBuffer();

	int tempBufferIndex = _frontBufferIndex;
	_frontBufferIndex = _backBufferIndex;
	_backBufferIndex = tempBufferIndex;
}

void Console::clearBuffer(char clearChar, WORD clearColour) {
	_clearChar = clearChar;

	for (unsigned short i = 0; i < _bufferSize; i++) {
		CHAR_INFO& tile = _renderBuffer[i];
		tile.Char.AsciiChar = clearChar;
		tile.Attributes = clearColour;
	}
}

void Console::clearScreen(char clearChar, WORD clearColour) {
	DWORD USELESS;
	FillConsoleOutputCharacterA(getBackBuffer(), clearChar, _bufferSize, _origin, &USELESS);
	FillConsoleOutputAttribute(getBackBuffer(), clearColour, _bufferSize, _origin, &USELESS);
}

void Console::showDefaultBuffer() {	SetConsoleActiveScreenBuffer(_hIn); }

const COORD& Console::getDimensions() const { return _dimensions; }
DWORD Console::getSize() const { return _bufferSize; }
SMALL_RECT Console::getBoundingBox() const { return _boundingBox; }


void Console::setFontSize(int size) {
	GetCurrentConsoleFontEx(getFrontBuffer(), true, &_fontInfo);

	_fontInfo.dwFontSize.X = size;
	_fontInfo.dwFontSize.Y = size;

	SetCurrentConsoleFontEx(GetConsoleWindow(), true, &_fontInfo);
	_fontSize = GetConsoleFontSize(getFrontBuffer(), _fontInfo.nFont);

	_dimensions = GetLargestConsoleWindowSize(getFrontBuffer());
	_window = SMALL_RECT{ 0, 0, _dimensions.X - 1, _dimensions.Y - 1 };
	_boundingBox = SMALL_RECT{ 0, 0, _dimensions.X, _dimensions.Y };

	SetConsoleScreenBufferSize(getFrontBuffer(), _dimensions);
	SetConsoleScreenBufferSize(getBackBuffer(), _dimensions);
	SetConsoleWindowInfo(getFrontBuffer(), true, &_window);
	SetConsoleWindowInfo(getBackBuffer(), true, &_window);

	_bufferSize = _dimensions.X * _dimensions.Y;
	_renderBuffer = new CHAR_INFO[_bufferSize];
	clearBuffer();
}
COORD Console::getFontSize() { return _fontSize; }

void Console::showFrontBuffer() { SetConsoleActiveScreenBuffer(getFrontBuffer()); }
void Console::showBackBuffer() { SetConsoleActiveScreenBuffer(getBackBuffer()); }
HANDLE& Console::getFrontBuffer() { return _buffers[_frontBufferIndex]; }
HANDLE& Console::getBackBuffer() { return _buffers[_backBufferIndex]; }
