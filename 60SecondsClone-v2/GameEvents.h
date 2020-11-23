#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

typedef std::string string;
typedef std::ifstream fStream;

#ifndef GAME_EVENTS_H
#define GAME_EVENTS_H

class GameEvent {
public:	
	GameEvent();
	GameEvent(COORD dimensions, CHAR_INFO* buffer);
	GameEvent(int width, int height, CHAR_INFO* buffer);

	COORD dimensions;
	CHAR_INFO* renderBuffer;
};

enum GameEvents : unsigned int {
	SPECIAL_EVENT_1,
	SPECIAL_EVENT_2,
	SPECIAL_EVENT_3,
	SPECIAL_EVENT_4,
	SPECIAL_EVENT_5,
	SPECIAL_EVENT_6,
	SPECIAL_EVENT_7,
	SPECIAL_EVENT_8,
	
	MILITARY_SAVE,
	
	NUM_EVENTS
};

enum FlavourText : unsigned int {
	FLAVOUR_TEXT_1 = GameEvents::NUM_EVENTS,
	FLAVOUR_TEXT_2,
	FLAVOUR_TEXT_3,
	FLAVOUR_TEXT_4,
	FLAVOUR_TEXT_5,
	FLAVOUR_TEXT_6,
	FLAVOUR_TEXT_7,
	FLAVOUR_TEXT_8,

	NUM_FLAVOURS = FLAVOUR_TEXT_8 + 1 - GameEvents::NUM_EVENTS
};

class EventCache {
public:
	static void initialize();
	static const GameEvent& get(int gameEvent);

protected:
	static GameEvent load(const char* filePath);

private:
	static GameEvent* _eventCache;
};

enum Outcomes : unsigned int {
	EVENT_1_IGNORE,
	EVENT_1_OUTCOME_1,
	EVENT_1_OUTCOME_2,
	EVENT_1_OUTCOME_3,
	EVENT_1_OUTCOME_4,
	EVENT_1_OUTCOME_5,
	EVENT_1_OUTCOME_6,

	EVENT_2_IGNORE,
	EVENT_2_OUTCOME_1,
	EVENT_2_OUTCOME_2,
	EVENT_2_OUTCOME_3,
	EVENT_2_OUTCOME_4,
	EVENT_2_OUTCOME_5,
	EVENT_2_OUTCOME_6,

	EVENT_3_IGNORE,
	EVENT_3_OUTCOME_1,
	EVENT_3_OUTCOME_2,
	EVENT_3_OUTCOME_3,
	EVENT_3_OUTCOME_4,
	EVENT_3_OUTCOME_5,
	EVENT_3_OUTCOME_6,

	EVENT_4_IGNORE,
	EVENT_4_OUTCOME_1,
	EVENT_4_OUTCOME_2,
	EVENT_4_OUTCOME_3,
	EVENT_4_OUTCOME_4,
	EVENT_4_OUTCOME_5,
	EVENT_4_OUTCOME_6,

	EVENT_5_IGNORE,
	EVENT_5_OUTCOME_1,
	EVENT_5_OUTCOME_2,
	EVENT_5_OUTCOME_3,
	EVENT_5_OUTCOME_4,
	EVENT_5_OUTCOME_5,
	EVENT_5_OUTCOME_6,

	EVENT_6_IGNORE,
	EVENT_6_OUTCOME_1,
	EVENT_6_OUTCOME_2,
	EVENT_6_OUTCOME_3,
	EVENT_6_OUTCOME_4,
	EVENT_6_OUTCOME_5,
	EVENT_6_OUTCOME_6,

	EVENT_7_IGNORE_1,
	EVENT_7_IGNORE_2,
	EVENT_7_OUTCOME_1,
	EVENT_7_OUTCOME_2,
	EVENT_7_OUTCOME_3,
	EVENT_7_OUTCOME_4,
	EVENT_7_OUTCOME_5,

	EVENT_8_IGNORE,
	EVENT_8_OUTCOME_1,
	EVENT_8_OUTCOME_2,
	EVENT_8_OUTCOME_3,
	EVENT_8_OUTCOME_4,
	EVENT_8_OUTCOME_5,
	EVENT_8_OUTCOME_6,

	FIRST_DAY,
	NO_OUTCOME,
	MILITARY_OUTCOME,

	NUM_OUTCOMES
};

class OutcomeCache : public EventCache {
public:
	static void initialize();
	static const GameEvent& get(int outcome);

private:
	static GameEvent* _outcomeCache;
};

#endif