#pragma once

#include "Character.h"
#include "Console.h"
#include "Events.h"
#include "GameEvents.h"
#include "Input.h"
#include "Item.h"
#include "Random.h"
#include "Sound.h"
#include "Sprite.h"

#include <chrono>
#include <ctime>
#include <math.h>
#include <vector>
#include <string>
#include <Windows.h>

#define FRAME_RATE 60

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

typedef std::string string;
typedef std::chrono::high_resolution_clock Clock;

enum GameState : unsigned int {
	MAIN_MENU,
	INSTRUCTIONS_MENU,
	SCAVENGE,

	SURVIVAL_NEW_DAY,
	SURVIVAL_STATUS,
	SURVIVAL_RATION,
	SURVIVAL_EVENT,

	GAME_OVER
};