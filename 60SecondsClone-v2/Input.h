#pragma once

#include "Events.h"
#include <Windows.h>

#ifndef INPUT_H
#define INPUT_H

class Input {
public:
	static bool isEvent(unsigned char event) {
		return GetAsyncKeyState(event);
	}
};

#endif