#include "GameEvents.h"

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

GameEvent::GameEvent() {}
GameEvent::GameEvent(COORD dimensions, CHAR_INFO* buffer) : dimensions(dimensions), renderBuffer(buffer) {}
GameEvent::GameEvent(int width, int height, CHAR_INFO* buffer) : GameEvent(COORD{ (SHORT)width, (SHORT)height }, buffer) {}

GameEvent* EventCache::_eventCache;
GameEvent* OutcomeCache::_outcomeCache;

void EventCache::initialize() {
	_eventCache = new GameEvent[GameEvents::NUM_EVENTS + FlavourText::NUM_FLAVOURS];
	
	_eventCache[GameEvents::SPECIAL_EVENT_1] = load("events/special-events/event-start/special-event-1");
	_eventCache[GameEvents::SPECIAL_EVENT_2] = load("events/special-events/event-start/special-event-2");
	_eventCache[GameEvents::SPECIAL_EVENT_3] = load("events/special-events/event-start/special-event-3");
	_eventCache[GameEvents::SPECIAL_EVENT_4] = load("events/special-events/event-start/special-event-4");
	_eventCache[GameEvents::SPECIAL_EVENT_5] = load("events/special-events/event-start/special-event-5");
	_eventCache[GameEvents::SPECIAL_EVENT_6] = load("events/special-events/event-start/special-event-6");
	_eventCache[GameEvents::SPECIAL_EVENT_7] = load("events/special-events/event-start/special-event-7");
	_eventCache[GameEvents::SPECIAL_EVENT_8] = load("events/special-events/event-start/special-event-8");
											 
											 
	_eventCache[FlavourText::FLAVOUR_TEXT_1] = load("events/flavour-text/flavour-text-1");
	_eventCache[FlavourText::FLAVOUR_TEXT_2] = load("events/flavour-text/flavour-text-2");
	_eventCache[FlavourText::FLAVOUR_TEXT_3] = load("events/flavour-text/flavour-text-3");
	_eventCache[FlavourText::FLAVOUR_TEXT_4] = load("events/flavour-text/flavour-text-4");
	_eventCache[FlavourText::FLAVOUR_TEXT_5] = load("events/flavour-text/flavour-text-5");
	_eventCache[FlavourText::FLAVOUR_TEXT_6] = load("events/flavour-text/flavour-text-6");
	_eventCache[FlavourText::FLAVOUR_TEXT_7] = load("events/flavour-text/flavour-text-7");
	_eventCache[FlavourText::FLAVOUR_TEXT_8] = load("events/flavour-text/flavour-text-8");
	
	_eventCache[GameEvents::MILITARY_SAVE]   = load("events/special-events/event-start/military-save");
}

void OutcomeCache::initialize() {
	_outcomeCache = new GameEvent[NUM_OUTCOMES];

	_outcomeCache[Outcomes::EVENT_1_IGNORE]    = load("events/special-events/outcomes/special-event-1/outcome-0");
	_outcomeCache[Outcomes::EVENT_1_OUTCOME_1] = load("events/special-events/outcomes/special-event-1/outcome-1");
	_outcomeCache[Outcomes::EVENT_1_OUTCOME_2] = load("events/special-events/outcomes/special-event-1/outcome-2");
	_outcomeCache[Outcomes::EVENT_1_OUTCOME_3] = load("events/special-events/outcomes/special-event-1/outcome-3");
	_outcomeCache[Outcomes::EVENT_1_OUTCOME_4] = load("events/special-events/outcomes/special-event-1/outcome-4");
	_outcomeCache[Outcomes::EVENT_1_OUTCOME_5] = load("events/special-events/outcomes/special-event-1/outcome-5");
	_outcomeCache[Outcomes::EVENT_1_OUTCOME_6] = load("events/special-events/outcomes/special-event-1/outcome-6");

	_outcomeCache[Outcomes::EVENT_2_IGNORE]    = load("events/special-events/outcomes/special-event-2/outcome-0");
	_outcomeCache[Outcomes::EVENT_2_OUTCOME_1] = load("events/special-events/outcomes/special-event-2/outcome-1");
	_outcomeCache[Outcomes::EVENT_2_OUTCOME_2] = load("events/special-events/outcomes/special-event-2/outcome-2");
	_outcomeCache[Outcomes::EVENT_2_OUTCOME_3] = load("events/special-events/outcomes/special-event-2/outcome-3");
	_outcomeCache[Outcomes::EVENT_2_OUTCOME_4] = load("events/special-events/outcomes/special-event-2/outcome-4");
	_outcomeCache[Outcomes::EVENT_2_OUTCOME_5] = load("events/special-events/outcomes/special-event-2/outcome-5");
	_outcomeCache[Outcomes::EVENT_2_OUTCOME_6] = load("events/special-events/outcomes/special-event-2/outcome-6");

	_outcomeCache[Outcomes::EVENT_3_IGNORE]    = load("events/special-events/outcomes/special-event-3/outcome-0");
	_outcomeCache[Outcomes::EVENT_3_OUTCOME_1] = load("events/special-events/outcomes/special-event-3/outcome-1");
	_outcomeCache[Outcomes::EVENT_3_OUTCOME_2] = load("events/special-events/outcomes/special-event-3/outcome-2");
	_outcomeCache[Outcomes::EVENT_3_OUTCOME_3] = load("events/special-events/outcomes/special-event-3/outcome-3");
	_outcomeCache[Outcomes::EVENT_3_OUTCOME_4] = load("events/special-events/outcomes/special-event-3/outcome-4");
	_outcomeCache[Outcomes::EVENT_3_OUTCOME_5] = load("events/special-events/outcomes/special-event-3/outcome-5");
	_outcomeCache[Outcomes::EVENT_3_OUTCOME_6] = load("events/special-events/outcomes/special-event-3/outcome-6");

	_outcomeCache[Outcomes::EVENT_4_IGNORE]    = load("events/special-events/outcomes/special-event-4/outcome-0");
	_outcomeCache[Outcomes::EVENT_4_OUTCOME_1] = load("events/special-events/outcomes/special-event-4/outcome-1");
	_outcomeCache[Outcomes::EVENT_4_OUTCOME_2] = load("events/special-events/outcomes/special-event-4/outcome-2");
	_outcomeCache[Outcomes::EVENT_4_OUTCOME_3] = load("events/special-events/outcomes/special-event-4/outcome-3");
	_outcomeCache[Outcomes::EVENT_4_OUTCOME_4] = load("events/special-events/outcomes/special-event-4/outcome-4");
	_outcomeCache[Outcomes::EVENT_4_OUTCOME_5] = load("events/special-events/outcomes/special-event-4/outcome-4");
	_outcomeCache[Outcomes::EVENT_4_OUTCOME_6] = load("events/special-events/outcomes/special-event-4/outcome-4");

	_outcomeCache[Outcomes::EVENT_5_IGNORE]    = load("events/special-events/outcomes/special-event-5/outcome-0");
	_outcomeCache[Outcomes::EVENT_5_OUTCOME_1] = load("events/special-events/outcomes/special-event-5/outcome-1");
	_outcomeCache[Outcomes::EVENT_5_OUTCOME_2] = load("events/special-events/outcomes/special-event-5/outcome-2");
	_outcomeCache[Outcomes::EVENT_5_OUTCOME_3] = load("events/special-events/outcomes/special-event-5/outcome-3");
	_outcomeCache[Outcomes::EVENT_5_OUTCOME_4] = load("events/special-events/outcomes/special-event-5/outcome-4");
	_outcomeCache[Outcomes::EVENT_5_OUTCOME_5] = load("events/special-events/outcomes/special-event-5/outcome-5");
	_outcomeCache[Outcomes::EVENT_5_OUTCOME_6] = load("events/special-events/outcomes/special-event-5/outcome-6");

	_outcomeCache[Outcomes::EVENT_6_IGNORE]    = load("events/special-events/outcomes/special-event-6/outcome-0");
	_outcomeCache[Outcomes::EVENT_6_OUTCOME_1] = load("events/special-events/outcomes/special-event-6/outcome-1");
	_outcomeCache[Outcomes::EVENT_6_OUTCOME_2] = load("events/special-events/outcomes/special-event-6/outcome-2");
	_outcomeCache[Outcomes::EVENT_6_OUTCOME_3] = load("events/special-events/outcomes/special-event-6/outcome-3");
	_outcomeCache[Outcomes::EVENT_6_OUTCOME_4] = load("events/special-events/outcomes/special-event-6/outcome-4");
	_outcomeCache[Outcomes::EVENT_6_OUTCOME_5] = load("events/special-events/outcomes/special-event-6/outcome-5");
	_outcomeCache[Outcomes::EVENT_6_OUTCOME_6] = load("events/special-events/outcomes/special-event-6/outcome-6");

	_outcomeCache[Outcomes::EVENT_7_IGNORE_1]  = load("events/special-events/outcomes/special-event-7/outcome-0");
	_outcomeCache[Outcomes::EVENT_7_IGNORE_2]  = load("events/special-events/outcomes/special-event-7/outcome-1");
	_outcomeCache[Outcomes::EVENT_7_OUTCOME_1] = load("events/special-events/outcomes/special-event-7/outcome-2");
	_outcomeCache[Outcomes::EVENT_7_OUTCOME_2] = load("events/special-events/outcomes/special-event-7/outcome-3");
	_outcomeCache[Outcomes::EVENT_7_OUTCOME_3] = load("events/special-events/outcomes/special-event-7/outcome-4");
	_outcomeCache[Outcomes::EVENT_7_OUTCOME_4] = load("events/special-events/outcomes/special-event-7/outcome-5");
	_outcomeCache[Outcomes::EVENT_7_OUTCOME_5] = load("events/special-events/outcomes/special-event-7/outcome-5");

	_outcomeCache[Outcomes::EVENT_8_IGNORE]    = load("events/special-events/outcomes/special-event-8/outcome-0");
	_outcomeCache[Outcomes::EVENT_8_OUTCOME_1] = load("events/special-events/outcomes/special-event-8/outcome-1");
	_outcomeCache[Outcomes::EVENT_8_OUTCOME_2] = load("events/special-events/outcomes/special-event-8/outcome-2");
	_outcomeCache[Outcomes::EVENT_8_OUTCOME_3] = load("events/special-events/outcomes/special-event-8/outcome-3");
	_outcomeCache[Outcomes::EVENT_8_OUTCOME_4] = load("events/special-events/outcomes/special-event-8/outcome-4");
	_outcomeCache[Outcomes::EVENT_8_OUTCOME_5] = load("events/special-events/outcomes/special-event-8/outcome-5");
	_outcomeCache[Outcomes::EVENT_8_OUTCOME_6] = load("events/special-events/outcomes/special-event-8/outcome-6");

	_outcomeCache[Outcomes::FIRST_DAY]			= load("events/special-events/outcomes/day-1");
	_outcomeCache[Outcomes::NO_OUTCOME]			= load("events/special-events/outcomes/no-outcome");
	_outcomeCache[Outcomes::MILITARY_OUTCOME]	= load("events/special-events/outcomes/military-save");
}

const GameEvent& EventCache::get(int gameEvent) { return _eventCache[gameEvent]; }
const GameEvent& OutcomeCache::get(int outcome) { return _outcomeCache[outcome]; }

GameEvent EventCache::load(const char* filePath) {
	string end = ".txt";
	string path = filePath + end;
	string line;
	std::vector<string> contents;

	fStream file(path);

	int textWidth = 0, textHeight = 0;

	while (std::getline(file, line)) {
		contents.push_back(line);
		if (line.length() > textWidth) textWidth = line.length();
	}
	textHeight = (int)contents.size();

	CHAR_INFO* eventBlock = new CHAR_INFO[textWidth * textHeight];
	for (unsigned int i = 0; i < textHeight; i++) {
		for (unsigned int j = 0; j < textWidth; j++) {
			int index = i * textWidth + j;

			if (contents[i].length() < j) eventBlock[index].Char.AsciiChar = ' ';
			else eventBlock[index].Char.AsciiChar = contents[i][j];
			eventBlock[index].Attributes = WHITE;
		}
	}

	file.close();
	return GameEvent(textWidth, textHeight, eventBlock);
}

