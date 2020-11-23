#pragma once
#include <Windows.h>

bool contains(const SMALL_RECT& container, const SMALL_RECT& object) {
	if (object.Left > container.Left && object.Right < container.Right &&
		object.Top > container.Top && object.Bottom < container.Bottom)
		return true;
	return false;
}

SMALL_RECT translatedObject(const SMALL_RECT& object, const COORD& translation) {
	return SMALL_RECT{
		object.Left + translation.X,
		object.Right + translation.X,
		object.Top + translation.Y,
		object.Bottom + translation.Y
	};
}

SMALL_RECT translatedObject(const SMALL_RECT& object, int x, int y) {
	return translatedObject(object, COORD{ (SHORT)x, (SHORT)y });
}