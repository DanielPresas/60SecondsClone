//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////   ________    _______													   ///////////////////////////////
////////////////////////  |   _____|  |   _   |													   ///////////////////////////////
////////////////////////  |  |        |  | |  |													   ///////////////////////////////
////////////////////////  |  |_____   |  | |  |													   ///////////////////////////////
////////////////////////  |   ___  |  |  | |  |													   ///////////////////////////////
////////////////////////  |  |___| |  |  |_|  |													   ///////////////////////////////
////////////////////////  |________|  |_______|													   ///////////////////////////////
////////////////////////          ____    ____    ____    _____    _____    ____     ____     _	   ///////////////////////////////
////////////////////////         |  __|  |  __|  |  __|  |  _  |  |  _  |  |  _ \   |  __|   | |   ///////////////////////////////
////////////////////////         | |__   | |__   | |     | | | |  | | | |  | | | |  | |__    | |   ///////////////////////////////
////////////////////////         |__  |  |  __|  | |     | | | |  | | | |  | | | |  |__  |   |_|   ///////////////////////////////
////////////////////////          __| |  | |__   | |__   | |_| |  | | | |  | |_| |   __| |    _	   ///////////////////////////////
////////////////////////         |____|  |____|  |____|  |_____|  |_| |_|  |____/   |____|   |_|   ///////////////////////////////
////////////////////////                                                                           ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////  GRAPHICS ENGINE BASED OFF OF GPC PRESIDENT'S (CONNOR - VICE TEAM LEADER)  ///////////////////////////////
////////////////////////////////////////////  COPYRIGHT THE G3NTS, 2018  //////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"

bool endGame = false, dedniel = false, saved = false;

int main() {

	/////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////  INITIAL MEMORY ALLOCATION  ////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////

	// Frame time tracking (for visual smoothness and for timers and stuff)
	Clock::time_point start;
	Clock::time_point end;
	Clock::duration duration;
	
	// Console window that we will render to
	Console console;
	
	// Initialize all sprites and events
	SpriteCache::initialize();
	EventCache::initialize();
	OutcomeCache::initialize();
	
	// ------------------------- CHARACTERS -----------------------------

	Character Daniel(SpriteCache::get(Sprites::DANIEL), 3);
	Character Edward(SpriteCache::get(Sprites::EDWARD));
	Character DelenTia(SpriteCache::get(Sprites::DELENTIA), 3);
	Character Tavis(SpriteCache::get(Sprites::TAVIS));
	
	// --------------------- CONSUMABLES & ITEMS ------------------------
	
	std::vector<Item> soupCans;
	std::vector<Item> waterBottles;
	std::vector<Item> medkits;

	for (unsigned int i = 0; i < 10; i++) {
		Item Soup(SpriteCache::get(Sprites::SOUP));
		soupCans.push_back(Soup);
	}
	
	for (unsigned int i = 0; i < 10; i++) {
		Item Water(SpriteCache::get(Sprites::WATER));
		waterBottles.push_back(Water);
	}
	
	for (unsigned int i = 0; i < 3; i++) {
		Item Medkit(SpriteCache::get(Sprites::MEDKIT));
		medkits.push_back(Medkit);
	}

	
	Item Radio(SpriteCache::get(Sprites::RADIO), 2);
	Item Map(SpriteCache::get(Sprites::MAP), 2);
	Item Pistol(SpriteCache::get(Sprites::PISTOL), 3);
	Item RatPoison(SpriteCache::get(Sprites::RAT_POISON), 2);
	Item Axe(SpriteCache::get(Sprites::AXE), 3);
	

	// --------------------- GAME START OBJECTS ------------------------

	Object titleScreen(SpriteCache::get(Sprites::TITLE_SCREEN));
	Object devLogo(SpriteCache::get(Sprites::DEV_LOGO));
	Object border(SpriteCache::get(Sprites::BORDER));

	// ------------------------ MENU OBJECTS ----------------------------

	Object copyright(SpriteCache::get(Sprites::COPYRIGHT));
	
	Object startButton;
	Object instructionsButton;
	Object exitButton;

	Object loading("\n   LOADING...   \n", YELLOW | INTENSIFY | RED_BACK);
	Object countdown;

	// -------------------- INSTRUCTIONS OBJECTS ------------------------

	Object instructions(SpriteCache::get(Sprites::INSTRUCTIONS));

	// ---------------------- SCAVENGE OBJECTS --------------------------

	Object level(SpriteCache::get(Sprites::LEVEL));
	Object shelterHatch(SpriteCache::get(Sprites::SHELTER_HATCH));

	Object invBorder(" Inventory\n|--------------------\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|\n|--------------------", YELLOW);
	Object controls("\n  [W] [A] [S] [D] to move  \n\n  [Space] to pick up objects  \n", YELLOW | INTENSIFY | RED_BACK);
	
	int time = 0;
	Object timer;

	std::vector<Object> scavengeInv;
	std::vector<Object> survivalInv;

	// ----------------------- SURVIVAL OBJECTS --------------------------
	
	Object invHeading("\n       YOUR INVENTORY:      \n", YELLOW | INTENSIFY | RED_BACK);
	Object chrHeading("\n    CHARACTERS REMAINING:   \n", YELLOW | INTENSIFY | RED_BACK);
	Object dayHeading;

	Object notebook(SpriteCache::get(Sprites::NOTEBOOK));
	Object notebookText;
	
	Object option1Button, option2Button, option3Button, option4Button;
	string option1, option2, option3, option4;

	Object statusText, selectionBar;
	string statusBuffer, chrName;

	GameEvent survivalEvent, eventOutcome;

	std::vector<Character> characters;
	std::vector<Item> inventory;

	std::vector<int> usedGameEvents, usedFlavourText;

	bool gameEvent = false, eventPresent;

	int day = 0, optionChosen = 100;
	int outcome, randomEvent, randomPerson;

	// ------------------------ GAME OVER OBJECTS ------------------------

	Object gameOverWin(SpriteCache::get(GAME_OVER_WIN));
	Object gameOverLose(SpriteCache::get(GAME_OVER_LOSE));

	// ---------------------- MISCELLANEOUS OBJECTS ----------------------

	Object goBack;
	Object goForward;

	// ------------------------- OTHER VARIABLES -------------------------

	POINT mousePos;
	COORD fontSize;
	COORD mouse;

	const int buttonWait = 80;
	const int maxInvSize = 4;
	const int columns = 4;

	const int complainHunger = 4, complainThirst = 3;
	const int maxSickDays = 5;
	const int maxHungryDays = complainHunger + 5;
	const int maxThirstyDays = complainThirst + 3;

	bool hasItem;
	
	double timerUpdate = 0;
	double frameTime = 0;

	//////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////  SPLASH SCREENS  ////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	
	SetConsoleTitle("60 Seconds!");

	console.clearBuffer();
	devLogo.setPosition(console.getDimensions().X / 2 - devLogo.getDimensions().X / 2,
						console.getDimensions().Y / 2 - devLogo.getDimensions().Y / 2);
	devLogo.addTo(console);
	
	console.render();

	playMusic("audio/menu.wav");
	Sleep(4000);
	
	console.clearBuffer();
	titleScreen.setPosition(console.getDimensions().X / 2 - titleScreen.getDimensions().X / 2,
							console.getDimensions().Y / 2 - titleScreen.getDimensions().Y / 2);
	titleScreen.addTo(console);
	
	console.render();
	Sleep(4000);

	/////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////   PRE-GAME ADJUSMENTS   ////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////

	GameState state = MAIN_MENU;
	
	border.setPosition(0, 0);

	titleScreen.setPosition(console.getDimensions().X / 2 - titleScreen.getDimensions().X / 2,
		console.getDimensions().Y / 3 - 20);
	copyright.setPosition(console.getDimensions().X / 2 - copyright.getDimensions().X / 2,
		console.getDimensions().Y - copyright.getDimensions().Y - 1);
	
	level.setPosition(1, console.getDimensions().Y / 2 - level.getDimensions().Y / 2);
	shelterHatch.setPosition(level.getDimensions().X - shelterHatch.getDimensions().X - 2, 
		level.getDimensions().Y / 2 - shelterHatch.getDimensions().Y / 2);
	invBorder.setPosition(console.getDimensions().X - invBorder.getDimensions().X - 1,
		console.getDimensions().Y / 2 - invBorder.getDimensions().Y / 2);
	controls.setPosition(15 * console.getDimensions().X / 16 - controls.getDimensions().X / 2,
		console.getDimensions().Y - controls.getDimensions().Y - 1);

	notebook.setPosition(console.getDimensions().X / 2 - notebook.getDimensions().X / 2,
		console.getDimensions().Y / 2 - notebook.getDimensions().Y / 2);
	invHeading.setPosition(console.getDimensions().X / 8 - invHeading.getDimensions().X / 2,
		console.getDimensions().Y / 2 - invHeading.getDimensions().X / 2 - 20);
	chrHeading.setPosition(console.getDimensions().X / 8 * 7 - chrHeading.getDimensions().X / 2,
		console.getDimensions().Y / 2 - chrHeading.getDimensions().X / 2 - 20);

	/////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////   MAIN GAME LOOP   //////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////
	while (!endGame) {		
		console.clearBuffer();
		border.addTo(console);

		fontSize = console.getFontSize();
		GetCursorPos(&mousePos);
		ScreenToClient(GetConsoleWindow(), &mousePos);
		mouse = { (SHORT)(mousePos.x / fontSize.X), (SHORT)(mousePos.y / fontSize.Y) };

		start = Clock::now();

		switch (state) {

		///////////////////////////////   Menu Screen   //////////////////////////////////////

		case MAIN_MENU:
			if (mouse.X > startButton.getPosition().X && mouse.X < startButton.getPosition().X + startButton.getDimensions().X &&
				mouse.Y > startButton.getPosition().Y && mouse.Y < startButton.getPosition().Y + startButton.getDimensions().Y) {
				
				if (Input::isEvent(Events::Mouse_Left)) {
					stopMusic();
					loading.setPosition(console.getDimensions().X / 2 - loading.getDimensions().X / 2, console.getDimensions().Y / 2 - loading.getDimensions().Y / 2);
					loading.addTo(console);
					console.render();
					Sleep(2000);

					time = 60;
					
					Item::ItemCollection.clear();
					Character::AllCharacters.clear();

					scavengeInv.clear();
					survivalInv.clear();

					for (unsigned int i = 0; i < soupCans.size(); i++) Item::add(soupCans[i]);
					for (unsigned int i = 0; i < waterBottles.size(); i++) Item::add(waterBottles[i]);
					for (unsigned int i = 0; i < medkits.size(); i++) Item::add(medkits[i]);
					
					Item::add(Radio);
					Item::add(Map);
					Item::add(Pistol);
					Item::add(RatPoison);
					Item::add(Axe);


					Character::add(Daniel);
					Character::add(Edward);
					Character::add(DelenTia);
					Character::add(Tavis);


					for (unsigned int i = 0; i < Item::ItemCollection.size(); i++) {
						for (unsigned int j = 0; j < Item::ItemCollection.size(); j++) {
							if (Item::ItemCollection[i] != Item::ItemCollection[j]) {
								do {
									Item::ItemCollection[i].setPosition(
										randomInt(level.getPosition().X + 1, level.getDimensions().X - 90 - Item::ItemCollection[i].getDimensions().X),
										randomInt(level.getPosition().Y + 1, level.getDimensions().Y - Item::ItemCollection[i].getDimensions().Y)
									);
								} while (Object::checkCollision(Item::ItemCollection[i], Item::ItemCollection[j]));
							}
						}
					}

					for (unsigned int i = 0; i < Character::AllCharacters.size(); i++) {
						if (Character::AllCharacters[i] == Daniel) {
							Character::remove(Daniel);
							i--;
						}
						else {
							for (unsigned int j = 0; j < Character::AllCharacters.size(); j++) {
								if(Character::AllCharacters[i] != Character::AllCharacters[j]) {
									do {
										Character::AllCharacters[i].setPosition(
											randomInt(level.getPosition().X + 1, level.getDimensions().X - 90 - Character::AllCharacters[i].getDimensions().X),
											randomInt(level.getPosition().Y + 1, level.getDimensions().Y - Character::AllCharacters[i].getDimensions().Y)
										);
									} while (Object::checkCollision(Character::AllCharacters[i], Character::AllCharacters[j]));
								}
							}

							for (unsigned int j = 0; j < Item::ItemCollection.size(); j++) {
								do {
									Character::AllCharacters[i].setPosition(
										randomInt(level.getPosition().X + 1, level.getDimensions().X - Character::AllCharacters[i].getDimensions().X - 90),
										randomInt(level.getPosition().Y + 1, level.getDimensions().Y - Character::AllCharacters[i].getDimensions().Y - 1)
									);
								} while (Object::checkCollision(Character::AllCharacters[i], Item::ItemCollection[j]));
							}
						}
					}

					Daniel.setPosition(level.getDimensions().X - Daniel.getDimensions().X - 20, level.getDimensions().Y / 2);
					
					for (unsigned int i = 3; i > 0; i--) {
						console.clearBuffer();

						countdown = Object("\n\n    " + std::to_string(i) + "    \n\n\n", YELLOW | INTENSIFY | RED_BACK);
						countdown.setPosition(console.getDimensions().X / 2 - countdown.getDimensions().X / 2, console.getDimensions().Y / 2 - countdown.getDimensions().Y / 2);
						countdown.addTo(console);

						console.render();
						Sleep(1000);
					}

					playMusic("audio/scavenge.wav");

					saved = false;
					dedniel = false;

					state = SCAVENGE;
					
					break;
				}

				startButton = Object(SpriteCache::get(Sprites::NEW_GAME_SELECT));
			}
			else if (mouse.X > instructionsButton.getPosition().X && mouse.X < instructionsButton.getPosition().X + instructionsButton.getDimensions().X && 
					 mouse.Y > instructionsButton.getPosition().Y && mouse.Y < instructionsButton.getPosition().Y + instructionsButton.getDimensions().Y) {
				instructionsButton = Object(SpriteCache::get(Sprites::INSTRUCTIONS_SELECT));
				
				if (Input::isEvent(Events::Mouse_Left)) {
					state = INSTRUCTIONS_MENU;
					Sleep(buttonWait);
				}
			}
			else if (mouse.X > exitButton.getPosition().X && mouse.X < exitButton.getPosition().X + exitButton.getDimensions().X &&
					 mouse.Y > exitButton.getPosition().Y && mouse.Y < exitButton.getPosition().Y + exitButton.getDimensions().Y) {
				exitButton = Object(SpriteCache::get(Sprites::EXIT_SELECT));
				
				if (Input::isEvent(Events::Mouse_Left)) {
					endGame = true;
					Sleep(buttonWait);
					break;
				}
			}
			else {
				startButton = Object(SpriteCache::get(Sprites::NEW_GAME_BUTTON));
				instructionsButton = Object(SpriteCache::get(Sprites::INSTRUCTIONS_BUTTON));
				exitButton = Object(SpriteCache::get(Sprites::EXIT_BUTTON));

				if (Input::isEvent(Events::Mouse_Left)) {}
			}

			startButton.setPosition(console.getDimensions().X / 2 - startButton.getDimensions().X / 2,
				console.getDimensions().Y / 3 + 20);
			instructionsButton.setPosition(console.getDimensions().X / 2 - instructionsButton.getDimensions().X / 2,
				console.getDimensions().Y / 3 + 30);
			exitButton.setPosition(console.getDimensions().X / 2 - exitButton.getDimensions().X / 2,
				console.getDimensions().Y / 3 + 40);

			titleScreen.addTo(console);
			startButton.addTo(console);
			instructionsButton.addTo(console);
			exitButton.addTo(console);
			copyright.addTo(console);
			
			if (Input::isEvent(Events::Escape)) endGame = true;

			break;

		///////////////////////////////   Instructions Menu   //////////////////////////////////////
		case INSTRUCTIONS_MENU:
			instructionsButton.setPosition(console.getDimensions().X / 2 - instructionsButton.getDimensions().X / 2, 2);

			instructions.setPosition(console.getDimensions().X / 2 - instructions.getDimensions().X / 2,
				console.getDimensions().Y / 2 - instructions.getDimensions().Y / 2);
			goBack.setPosition(5, console.getDimensions().Y - goBack.getDimensions().Y - 3);

			instructionsButton.addTo(console);
			instructions.addTo(console);
			goBack.addTo(console);

			if (mouse.X > goBack.getPosition().X && mouse.X < goBack.getPosition().X + goBack.getDimensions().X &&
				mouse.Y > goBack.getPosition().Y && mouse.Y < goBack.getPosition().Y + goBack.getDimensions().Y) {
				goBack = Object("\n\n\n              BACK TO MENU              \n\n\n", YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {
					state = MAIN_MENU;
					Sleep(buttonWait);
					break;
				}
			}
			else {
				goBack = Object("\n\n\n              BACK TO MENU              \n\n\n", YELLOW | INTENSIFY | RED_BACK);

				if (Input::isEvent(Events::Mouse_Left)) {}
			}

			if (Input::isEvent(Events::Escape)) endGame = true;

			break;

		///////////////////////////////   Part 1: Scavenge   //////////////////////////////////////
		case SCAVENGE:
			if (Input::isEvent(Events::Escape)) {
				endGame = true;
				break;
			}

			timerUpdate += frameTime;
			if (timerUpdate >= 1.0) {
				time--;
				timerUpdate = 0;
			}
			
			level.addTo(console);
			invBorder.addTo(console);

			Daniel.updateTo(console);
			shelterHatch.addTo(console);

			if (Object::checkCollision(Daniel, shelterHatch)) {
				if (Input::isEvent(Events::Space)) {
					if (scavengeInv.size() > 0) {
						for (unsigned int i = 0; i < scavengeInv.size(); i++) {
							survivalInv.push_back(scavengeInv[i]);
							
							if (scavengeInv[i].getInvSize() > 1) {
								i += scavengeInv[i].getInvSize() - 1;
							}
						}

						while (!scavengeInv.empty()) {
							scavengeInv.pop_back();
						}
					}
				}
			}
			else {
				if (Input::isEvent(Events::Space)) {}
			}

			for (unsigned int i = 0; i < Item::ItemCollection.size(); i++) {
				if (Object::checkCollision(Daniel, Item::ItemCollection[i])) {
					if (scavengeInv.size() + Item::ItemCollection[i].getInvSize() <= maxInvSize) {
						if (Input::isEvent(Events::Space)) {
							if (Item::ItemCollection[i] == Radio) {
								for (unsigned int k = 0; k < Radio.getInvSize(); k++) {
									scavengeInv.push_back(Radio);
								}

								Item::remove(Radio);
								break;
							}
							else if (Item::ItemCollection[i] == Map) {
								for (unsigned int k = 0; k < Map.getInvSize(); k++) {
									scavengeInv.push_back(Map);
								}

								Item::remove(Map);
								break;
							}
							else if (Item::ItemCollection[i] == Pistol) {
								for (unsigned int k = 0; k < Pistol.getInvSize(); k++) {
									scavengeInv.push_back(Pistol);
								}

								Item::remove(Pistol);
								break;
							}
							else if (Item::ItemCollection[i] == RatPoison) {
								for (unsigned int k = 0; k < RatPoison.getInvSize(); k++) {
									scavengeInv.push_back(RatPoison);
								}

								Item::remove(RatPoison);
								break;
							}
							else if (Item::ItemCollection[i] == Axe) {
								for (unsigned int k = 0; k < Axe.getInvSize(); k++) {
									scavengeInv.push_back(Axe);
								}

								Item::remove(Axe);
								break;
							}
						}
						else Item::ItemCollection[i].addTo(console);
					}
					else Item::ItemCollection[i].addTo(console);
				}
				else Item::ItemCollection[i].addTo(console);
			}

			for (unsigned int i = 0; i < Item::ItemCollection.size(); i++) {
				if (Object::checkCollision(Daniel, Item::ItemCollection[i])) {
					if (scavengeInv.size() + Item::ItemCollection[i].getInvSize() <= maxInvSize) {
						if (Input::isEvent(Events::Space)) {
							for (unsigned int j = 0; j < soupCans.size(); j++) {
								if (Item::ItemCollection[i] == soupCans[j]) {
									scavengeInv.push_back(soupCans[j]);
									Item::remove(soupCans[j]);
									break;
								}
							}
						}
					}
					else Item::ItemCollection[i].addTo(console);
				}
				else Item::ItemCollection[i].addTo(console);
			}

			for (unsigned int i = 0; i < Item::ItemCollection.size(); i++) {
				if (Object::checkCollision(Daniel, Item::ItemCollection[i])) {
					if (scavengeInv.size() + Item::ItemCollection[i].getInvSize() <= maxInvSize) {
						if (Input::isEvent(Events::Space)) {
							for (unsigned int j = 0; j < waterBottles.size(); j++) {
								if (Item::ItemCollection[i] == waterBottles[j]) {
									scavengeInv.push_back(waterBottles[j]);
									Item::remove(waterBottles[j]);
									break;
								}
							}
						}
					}
					else Item::ItemCollection[i].addTo(console);
				}
				else Item::ItemCollection[i].addTo(console);
			}

			for (unsigned int i = 0; i < Item::ItemCollection.size(); i++) {
				if (Object::checkCollision(Daniel, Item::ItemCollection[i])) {
					if (scavengeInv.size() + Item::ItemCollection[i].getInvSize() <= maxInvSize) {
						if (Input::isEvent(Events::Space)) {
							for (unsigned int j = 0; j < medkits.size(); j++) {
								if (Item::ItemCollection[i] == medkits[j]) {
									scavengeInv.push_back(medkits[j]);
									Item::remove(medkits[j]);
									break;
								}
							}
						}
					}
					else Item::ItemCollection[i].addTo(console);
				}
				else Item::ItemCollection[i].addTo(console);
			}

			for (unsigned int i = 0; i < Character::AllCharacters.size(); i++) {
				if (Object::checkCollision(Daniel, Character::AllCharacters[i])) {
					if (scavengeInv.size() + Character::AllCharacters[i].getInvSize() <= maxInvSize) {
						if (Input::isEvent(Events::Space)) {
							if (Character::AllCharacters[i] == Edward) {
								for (unsigned int k = 0; k < Edward.getInvSize(); k++) {
									scavengeInv.push_back(Edward);
								}

								Character::remove(Edward);
								break;
							}
							else if (Character::AllCharacters[i] == DelenTia) {
								for (unsigned int k = 0; k < DelenTia.getInvSize(); k++) {
									scavengeInv.push_back(DelenTia);
								}

								Character::remove(DelenTia);
								break;
							}
							else if (Character::AllCharacters[i] == Tavis) {
								for (unsigned int k = 0; k < Tavis.getInvSize(); k++) {
									scavengeInv.push_back(Tavis);
								}

								Character::remove(Tavis);
								break;
							}
						}
						else Character::AllCharacters[i].addTo(console);
					}
					else Character::AllCharacters[i].addTo(console);
				}
				else Character::AllCharacters[i].addTo(console);
			}
			
			for (unsigned int i = 0; i < scavengeInv.size(); i++) {
				scavengeInv[i].setPosition(console.getDimensions().X - scavengeInv[i].getDimensions().X / 2 - invBorder.getDimensions().X / 2 - 1,
					console.getDimensions().Y / 2 - scavengeInv[i].getDimensions().Y / 2 - invBorder.getDimensions().Y / 2 + 10 + i * 10);
				scavengeInv[i].addTo(console);
			}

			if (time == 60) {
				timer = Object("\n  TIME REMAINING: \n\n       1:00\n", YELLOW | INTENSIFY | RED_BACK);
			}
			else if (time >= 10) {
				timer = Object("\n  TIME REMAINING: \n\n       0:" + std::to_string(time) + "\n", YELLOW | INTENSIFY | RED_BACK);
			}
			else if (time > 0) {
				timer = Object("\n  TIME REMAINING: \n\n       0:0" + std::to_string(time) + "\n", YELLOW | INTENSIFY | RED_BACK);
			}
			timer.setPosition(15 * console.getDimensions().X / 16 - timer.getDimensions().X / 2,
				console.getDimensions().Y / 4 - timer.getDimensions().Y / 2 - 20);
			
			timer.addTo(console);
			controls.addTo(console);

			if(time <= 0) {

				if (Object::checkCollision(Daniel, shelterHatch)) {
					state = SURVIVAL_NEW_DAY;
					day = 0;
				}
				else {
					dedniel = true;
					state = GAME_OVER;
				}

				stopMusic();
				loading.setPosition(console.getDimensions().X / 2 - loading.getDimensions().X / 2, console.getDimensions().Y / 2 - loading.getDimensions().Y / 2);
				loading.addTo(console);

				console.render();
				Sleep(2000);
				console.clearBuffer();


				characters.clear();
				inventory.clear();

				border.addTo(console);

				std::sort(survivalInv.begin(), survivalInv.end());

				for (unsigned int i = 0; i < survivalInv.size(); i++) {
					if (survivalInv[i].getType() == Types::CHARACTER) {
						if (survivalInv[i] == Daniel) characters.push_back(Daniel);
						else if (survivalInv[i] == Edward) characters.push_back(Edward);
						else if (survivalInv[i] == DelenTia) characters.push_back(DelenTia);
						else if (survivalInv[i] == Tavis) characters.push_back(Tavis);
					}
					else {

						if (survivalInv[i] == Radio) inventory.push_back(Radio);
						else if (survivalInv[i] == Map) inventory.push_back(Map);
						else if (survivalInv[i] == Pistol) inventory.push_back(Pistol);
						else if (survivalInv[i] == RatPoison) inventory.push_back(RatPoison);
						else if (survivalInv[i] == Axe) inventory.push_back(Axe);

						else {

							for (unsigned int j = 0; j < soupCans.size(); j++) {
								if (survivalInv[i] == soupCans[j]) {
									inventory.push_back(soupCans[j]);
								}
							}
							for (unsigned int j = 0; j < waterBottles.size(); j++)
								if (survivalInv[i] == waterBottles[j]) inventory.push_back(waterBottles[j]);
							
							for (unsigned int j = 0; j < medkits.size(); j++)
								if (survivalInv[i] == medkits[j]) inventory.push_back(medkits[j]);

						}
					}
				}

				characters.push_back(Daniel);

				std::sort(characters.begin(), characters.end());
				std::sort(inventory.begin(), inventory.end());

				playMusic("audio/survival.wav");
				Sleep(1000);
			}

			break;

		//////////////////////////////   Part 2: Survival   //////////////////////////////////////
		/////////////////////  2.0  Calculations and Splash Screen    ////////////////////////////
		case SURVIVAL_NEW_DAY:
			day++;

			if (gameEvent) {
				if (optionChosen == 0) {
					
					if (randomEvent == GameEvents::SPECIAL_EVENT_7) {
						outcome = randomInt(0, 1);

						switch (outcome) {
						case 1:
							eventOutcome = OutcomeCache::get(Outcomes::EVENT_7_IGNORE_1);
							break;

						case 2:
							eventOutcome = OutcomeCache::get(Outcomes::EVENT_7_IGNORE_2);
							break;
						}

						for (unsigned int i = 0; i < 3; i++) {
							for (unsigned int j = 0; j < soupCans.size(); j++) {
								if (std::find(inventory.begin(), inventory.end(), soupCans[j]) != inventory.end()) {
									inventory.erase(std::find(inventory.begin(), inventory.end(), soupCans[j]));
									break;
								}
							}
						}
					}
					else if (randomEvent == GameEvents::MILITARY_SAVE) {
						saved = true;
						eventOutcome = OutcomeCache::get(Outcomes::MILITARY_OUTCOME);
					}
					else eventOutcome = OutcomeCache::get(randomEvent * 7);
				
				}
				else {
					outcome = randomInt(1, 6);

					switch (randomEvent) {
					case GameEvents::SPECIAL_EVENT_1:

						switch (outcome) {
						case 1:
							break;
						case 2:
							dedniel = true;
							characters.clear();
							break;
						case 3:
							for (unsigned int i = 0; i < 3; i++) inventory.push_back(soupCans[i]);
							break;
						case 4:
							for (unsigned int i = 0; i < 2; i++) inventory.push_back(waterBottles[i]);
							break;
						case 5:
							randomPerson = randomInt(0, characters.size() - 1);
							characters[randomPerson].isSick = true;
							break;
						case 6:
							hasItem = false;
							for (unsigned int i = 0; i < inventory.size(); i++) {
								if (inventory[i] == Map) {
									hasItem = true;
									break;
								}
							}

							if (!hasItem) inventory.push_back(Map);

							break;
						}

						break;

					case GameEvents::SPECIAL_EVENT_2:

						switch (outcome) {
						case 1:
							dedniel = true;
							characters.clear();

							break;
						case 2:
							hasItem = false;
							for (unsigned int i = 0; i < inventory.size(); i++) {
								if (inventory[i] == Radio) {
									hasItem = true;
									break;
								}
							}

							if (!hasItem) inventory.push_back(Radio);

							break;
						case 3:
							randomPerson = randomInt(0, characters.size() - 1);
							characters[randomPerson].isSick = true;

							break;
						case 4:
							for (unsigned int i = 0; i < 1; i++) inventory.push_back(soupCans[i]);
							
							break;
						case 5:
							for (unsigned int i = 0; i < 3; i++) inventory.push_back(waterBottles[i]);
							
							break;
						case 6:
							break;
						}

						break;

					case GameEvents::SPECIAL_EVENT_3:

						switch (outcome) {
						case 1:
							dedniel = true;
							characters.clear();

							break;
						case 2:
							for (unsigned int i = 0; i < 1; i++) {
								inventory.push_back(soupCans[i]);
								inventory.push_back(waterBottles[i]);
							}

							break;
						case 3:
							break;
						case 4:
							for (unsigned int i = 0; i < 1; i++) inventory.push_back(soupCans[i]);

							break;
						case 5:
							for (unsigned int i = 0; i < 1; i++) inventory.push_back(waterBottles[i]);

							break;
						case 6:
							randomPerson = randomInt(0, characters.size() - 1);
							characters[randomPerson].isSick = true;

							break;
						}

						break;

					case GameEvents::SPECIAL_EVENT_4:

						switch (outcome) {
						case 1:
							break;
						case 2:
							hasItem = false;
							for (unsigned int i = 0; i < inventory.size(); i++) {
								if (inventory[i] == Pistol) {
									hasItem = true;
									break;
								}
							}

							if (!hasItem) inventory.push_back(Pistol);

							break;
						case 3:
							for (unsigned int i = 0; i < 3; i++) inventory.push_back(soupCans[i]);

							break;
						case 4:
						case 5:
						case 6:
							dedniel = true;
							characters.clear();

							break;
						}

						break;

					case GameEvents::SPECIAL_EVENT_5:

						switch (outcome) {
						case 1:
							break;
						case 2:
							dedniel = true;
							characters.clear();

							break;
						case 3:
							for (unsigned int i = 0; i < 1; i++) {
								inventory.push_back(soupCans[i]);
								inventory.push_back(waterBottles[i]);
							}

							break;
						case 4:
							for (unsigned int i = 0; i < 1; i++) inventory.push_back(soupCans[i]);

							break;
						case 5:
							for (unsigned int i = 0; i < 1; i++) inventory.push_back(waterBottles[i]);

							break;
						case 6:
							hasItem = false;
							for (unsigned int i = 0; i < inventory.size(); i++) {
								if (inventory[i] == RatPoison) {
									hasItem = true;
									break;
								}
							}

							if (!hasItem) inventory.push_back(RatPoison);

							break;
						}

						break;

					case GameEvents::SPECIAL_EVENT_6:
						
						switch (outcome) {
						case 1:
							for (unsigned int i = 0; i < 2; i++) inventory.push_back(soupCans[i]);

							break;
						case 2:
							for (unsigned int i = 0; i < 1; i++) inventory.push_back(soupCans[i]);

							break;
						case 3:
							dedniel = true;
							characters.clear();

							break;
						case 4:
							break;
						case 5:
							randomPerson = randomInt(0, characters.size() - 1);
							characters[randomPerson].isSick = true;

							break;

							break;
						case 6:
							for (unsigned int i = 0; i < characters.size(); i++) {
								characters[i].isSick = true;
							}

							break;
						}
						
						break;

					case GameEvents::SPECIAL_EVENT_7:

						switch (outcome) {
						case 1:
							for (unsigned int i = 0; i < 2; i++) inventory.push_back(soupCans[i]);
							for (unsigned int i = 0; i < 2; i++) inventory.push_back(waterBottles[i]);

							break;
						case 2:
						case 3:
						case 4:
						case 5:
						case 6:
							switch (optionChosen) {
							case 1:
								hasItem = false;
								for (unsigned int i = 0; i < inventory.size(); i++) {
									if (inventory[i] == Axe) {
										hasItem = true;
										break;
									}
								}

								if (hasItem) inventory.erase(std::find(inventory.begin(), inventory.end(), Axe));
								outcome = 3;

								break;

							case 2:
								hasItem = false;
								for (unsigned int i = 0; i < inventory.size(); i++) {
									if (inventory[i] == RatPoison) {
										hasItem = true;
										break;
									}
								}

								if (hasItem) inventory.erase(std::find(inventory.begin(), inventory.end(), RatPoison));
								outcome = 4;

								break;

							case 3:
								hasItem = false;
								for (unsigned int i = 0; i < inventory.size(); i++) {
									if (inventory[i] == Pistol) {
										hasItem = true;
										break;
									}
								}

								if (hasItem) inventory.erase(std::find(inventory.begin(), inventory.end(), Pistol));
								outcome = 5;

								break;
							}

							for (unsigned int i = 0; i < 2; i++) inventory.push_back(soupCans[i]);
							for (unsigned int i = 0; i < 2; i++) inventory.push_back(waterBottles[i]);

							break;

						}
						
						break;

					case GameEvents::SPECIAL_EVENT_8:

						switch (outcome) {
						case 1:
							for (unsigned int i = 0; i < 2; i++) {

								for (unsigned int j = 0; j < inventory.size(); j++) {
									for (unsigned int k = 0; k < soupCans.size(); k++) {
										if (inventory[j] == soupCans[k])
											inventory.erase(std::find(inventory.begin(), inventory.end(), soupCans[k]));
									}

									for (unsigned int k = 0; k < waterBottles.size(); k++) {
										if (inventory[j] == waterBottles[k])
											inventory.erase(std::find(inventory.begin(), inventory.end(), waterBottles[k]));
									}
								}

							}

							break;
						case 2:
							for (unsigned int i = 0; i < 3; i++) inventory.push_back(soupCans[i]);

							break;
						case 3:
							dedniel = true;
							characters.clear();

							break;
						case 4:
							inventory.push_back(medkits[0]);							

							break;
						case 5:
							for (unsigned int i = 0; i < characters.size(); i++) characters[i].thirstyDays += complainThirst;

							break;
						case 6:
							randomPerson = randomInt(0, characters.size() - 1);
							characters[randomPerson].isSick = true;

							break;
						}
						

						break;
					}

					eventOutcome = OutcomeCache::get(randomEvent * 7 + outcome);
				}
			}
			else eventOutcome = OutcomeCache::get(Outcomes::NO_OUTCOME);

			if (usedGameEvents.size() == GameEvents::NUM_EVENTS) usedGameEvents.clear();
			if (usedFlavourText.size() == FlavourText::NUM_FLAVOURS) usedFlavourText.clear();
			
			if (day == 1) {
				gameEvent = false;
				eventOutcome = OutcomeCache::get(Outcomes::FIRST_DAY);
			}
			else gameEvent = randomBool();

			if (gameEvent) {
				optionChosen = 100;

				do {
					eventPresent = false;

					if (std::find(inventory.begin(), inventory.end(), Radio) != inventory.end() &&
						std::find(inventory.begin(), inventory.end(), Map) != inventory.end() && 
						day >= 20) {
						randomEvent = randomInt(0, GameEvents::NUM_EVENTS - 1);
					}
					else randomEvent = randomInt(0, GameEvents::NUM_EVENTS - 2);
					
					for (unsigned int i = 0; i < usedGameEvents.size(); i++) {
						if (usedGameEvents[i] == randomEvent) {
							eventPresent = true;
							break;
						}
					}

				} while (eventPresent);
				usedGameEvents.push_back(randomEvent);

				switch (randomEvent) {
				case GameEvents::SPECIAL_EVENT_1:
					option1 = "\n     Leave the suitcase outside.   \n";
					option2 = "\n     Bring the suitcase inside.    \n";
					option3 = "";
					option4 = "";

					break;
				case GameEvents::SPECIAL_EVENT_2:
					option1 = "\n        Stay in the bunker.        \n";
					option2 = "\n   Send someone to help the girl.  \n";
					option3 = "";
					option4 = "";

					break;

				case GameEvents::SPECIAL_EVENT_3:
					option1 = "\n        Stay in the bunker.        \n";
					option2 = "\n     Pay the elderly a visit.      \n";
					option3 = "";
					option4 = "";

					break;

				case GameEvents::SPECIAL_EVENT_4:
					option1 = "\n        Stay in the bunker.        \n";
					option2 = "\n   Go to the survivor's meeting.   \n";
					option3 = "";
					option4 = "";

					break;

				case GameEvents::SPECIAL_EVENT_5:
					option1 = "\n   Let it ring for however long\n         it wants to ring.         \n";
					option2 = "\n       Go check out the noise.     \n";
					option3 = "";
					option4 = "";

					break;

				case GameEvents::SPECIAL_EVENT_6:
					option1 = "\n       Throw the soup away.        \n";
					option2 = "\n          Eat the soup.            \n";
					option3 = "";
					option4 = "";

					break;

				case GameEvents::SPECIAL_EVENT_7:
					option1 = "\n       Maybe it'll go away?        \n";

					for (unsigned int i = 0; i < inventory.size(); i++) {
						if (inventory[i] == Axe) {
							option2 = "\n      Investigate and use the      \n      axe to defend yourself.      \n";
							continue;
						}
						else option2 = "";

						if (inventory[i] == RatPoison) {
							option3 = "\n      Investigate and use the      \n   rat poison to defend yourself.  \n";
							continue;
						}
						else option3 = "";
						
						if (inventory[i] == Pistol) {
							option4 = "\n      Investigate and use the      \n     pistol to defend yourself.    \n";
							continue;
						}
						else option4 = "";
					}

					break;

				case GameEvents::SPECIAL_EVENT_8:
					option1 = "\n        Ignore the graffiti.       \n";
					option2 = "\n    Send someone to investigate.   \n";
					option3 = "";
					option4 = "";

					break;

				case GameEvents::MILITARY_SAVE:

					option1 = "\n           We're saved!            \n";
					option2 = "";
					option3 = "";
					option4 = "";

					break;
				}
			}
			else {
				optionChosen = 0;
				
				do {
					eventPresent = false;

					randomEvent = randomInt(GameEvents::NUM_EVENTS, GameEvents::NUM_EVENTS + FlavourText::NUM_FLAVOURS - 1);

					for (unsigned int i = 0; i < usedFlavourText.size(); i++) {
						if (usedFlavourText[i] == randomEvent) {
							eventPresent = true;
							break;
						}
					}

				} while (eventPresent);

				usedFlavourText.push_back(randomEvent);
			}
			
			survivalEvent = EventCache::get(randomEvent);

			statusBuffer = "";

			if (!saved) {
				for (unsigned int i = 0; i < characters.size(); i++) {
					if (characters[i] == Daniel) chrName = "Daniel";
					else if (characters[i] == Edward) chrName = "Edward";
					else if (characters[i] == DelenTia) chrName = "DelenTia";
					else if (characters[i] == Tavis) chrName = "Tavis";

					if (characters[i].hasMed) {
						characters[i].isSick = false;
						characters[i].sickDays = 0;

						for (unsigned int j = 0; j < medkits.size(); j++) {
							if (std::find(inventory.begin(), inventory.end(), medkits[j]) != inventory.end())
								inventory.erase(std::find(inventory.begin(), inventory.end(), medkits[j]));
							break;
						}
					}

					if (characters[i].hasFood) {
						characters[i].isHungry = false;
						characters[i].hungryDays = 0;
					}
					else characters[i].isHungry = true;

					if (characters[i].hasWater) {
						characters[i].isThirsty = false;
						characters[i].thirstyDays = 0;
					}
					else characters[i].isThirsty = true;

					characters[i].hasFood = false;
					characters[i].hasWater = false;
					characters[i].hasMed = false;

					int random;
					if (characters[i].isSick || characters[i].isHungry || characters[i].isThirsty) {
						if (characters[i].isSick) {
							characters[i].sickDays++;

							if (characters[i].sickDays > maxSickDays) {
								characters.erase(std::find(characters.begin(), characters.end(), characters[i]));
								statusBuffer += chrName + " has died to their illness overnight.\n\n\n\n";
								i--;
								continue;
							}
							else {
								random = randomInt(0, 3);
								switch (random) {
								case 0:
									statusBuffer += chrName + " feels a little under the weather.\n\n";
									break;
								case 1:
									statusBuffer += chrName + " has fallen ill.\n\n";
									break;
								case 2:
									statusBuffer += chrName + " could really use some medical attention.\n\n";
									break;
								case 3:
									statusBuffer += chrName + " would be okay, if they weren't sick.\n\n";
									break;
								}
							}
						}

						if (characters[i].isHungry) {
							characters[i].hungryDays++;
							if (characters[i].hungryDays > maxHungryDays) {
								characters.erase(std::find(characters.begin(), characters.end(), characters[i]));
								statusBuffer += chrName + " starved to death overnight.\n\n\n\n";
								i--;
								continue;
							}
							else if (characters[i].hungryDays >= complainHunger) {
								random = randomInt(0, 3);
								switch (random) {
								case 0:
									statusBuffer += chrName + " is feeling kinda hungry.\n\n";
									break;
								case 1:
									statusBuffer += chrName + " needs some food, like, now.\n\n";
									break;
								case 2:
									statusBuffer += chrName + " has been craving food for a while.\n\n";
									break;
								case 3:
									statusBuffer += chrName + " is starting to feel hungry. Some food would be nice.\n\n";
									break;
								}
							}
						}

						if (characters[i].isThirsty) {
							characters[i].thirstyDays++;

							if (characters[i].thirstyDays > maxThirstyDays) {
								characters.erase(std::find(characters.begin(), characters.end(), characters[i]));
								statusBuffer += chrName + " succumbed to dehydration overnight.\n\n\n\n";
								i--;
								continue;
							}
							else if (characters[i].thirstyDays >= complainThirst) {
								random = randomInt(0, 3);
								switch (random) {
								case 0:
									statusBuffer += chrName + " is parched. Some water would really help.\n\n";
									break;
								case 1:
									statusBuffer += chrName + " has been feeling thirsty. (Not that kind of thristy.)\n\n";
									break;
								case 2:
									statusBuffer += chrName + " is asking for water.\n\n";
									break;
								case 3:
									statusBuffer += chrName + " would feel better if he had a drink of water.\n\n";
									break;
								}
							}
						}

						if (!characters[i].isSick && characters[i].hungryDays < complainHunger && characters[i].thirstyDays < complainThirst) {
							random = randomInt(0, 3);

							switch (random) {
							case 0:
								statusBuffer += chrName + " is feeling okay. At least for now.\n\n";
								break;
							case 1:
								statusBuffer += chrName + " hasn't complained too much.\n\n";
								break;
							case 2:
								statusBuffer += chrName + " should be fine for a while.\n\n";
								break;
							case 3:
								statusBuffer += chrName + " doesn't really need anything right now.\n\n";
								break;
							}
						}
					}
					else {
						random = randomInt(0, 3);

						switch (random) {
						case 0:
							statusBuffer += chrName + " is feeling okay. At least for now.\n\n";
							break;
						case 1:
							statusBuffer += chrName + " hasn't complained too much.\n\n";
							break;
						case 2:
							statusBuffer += chrName + " should be fine for a while.\n\n";
							break;
						case 3:
							statusBuffer += chrName + " doesn't really need anything right now.\n\n";
							break;
						}
					}

					statusBuffer += "\n";
				}
			}
			else statusBuffer = "You survived for " + std::to_string(day - 1) + " days.";

			std::sort(inventory.begin(), inventory.end());
			
			if (characters.size() == 0) {
				statusBuffer = "You survived for " + std::to_string(day - 1) + " days.";
				dedniel = true;
			}

			console.clearBuffer();

			if (dedniel || saved) dayHeading = Object("\n\n\n\n               THE END               \n\n\n\n", YELLOW | INTENSIFY | RED_BACK);
			else dayHeading = Object("\n\n\n\n               DAY " + std::to_string(day) + "               \n\n\n\n", YELLOW | INTENSIFY | RED_BACK);

			dayHeading.setPosition(console.getDimensions().X / 2 - dayHeading.getDimensions().X / 2,
								   console.getDimensions().Y / 2 - dayHeading.getDimensions().Y / 2 - 20);
			dayHeading.addTo(console);
			console.render();
			Sleep(3000);

			state = SURVIVAL_STATUS;

			break;

		//////////////////////////////  2.1  Status Update  //////////////////////////////////////
		case SURVIVAL_STATUS:
			if (Input::isEvent(Events::Escape)) {
				endGame = true;
				break;
			}
			
			if (dedniel || saved) dayHeading = Object("\n     THE END     \n", YELLOW | INTENSIFY | RED_BACK);
			else dayHeading = Object("\n     DAY " + std::to_string(day) + "     \n", YELLOW | INTENSIFY | RED_BACK);
			
			notebookText = Object(eventOutcome);
			
			dayHeading.setPosition(console.getDimensions().X / 2 - dayHeading.getDimensions().X / 2 + 8,
								   console.getDimensions().Y / 2 - dayHeading.getDimensions().Y / 2 - 50);
			notebookText.setPosition(notebook.getPosition().X + notebook.getDimensions().X / 2 - 45,
									 notebook.getPosition().Y + notebook.getDimensions().Y / 2 - notebookText.getDimensions().Y / 2 - 30);
			
			chrHeading.addTo(console);
			invHeading.addTo(console);
			
			notebook.addTo(console);
			dayHeading.addTo(console);
			notebookText.addTo(console);
			
			for (unsigned int i = 0; i < characters.size(); i++) {				
				characters[i].setPosition(7 * console.getDimensions().X / 8 - characters[i].getDimensions().X / 2, 
										  console.getDimensions().Y / 2 + i * 20 - 20);
				characters[i].addTo(console);
			}

			statusText = Object(statusBuffer);
			statusText.setPosition(notebook.getPosition().X + notebook.getDimensions().X / 2 - 45,
				notebook.getPosition().Y + notebook.getDimensions().Y / 2 - statusText.getDimensions().Y / 2 + 10);
			statusText.addTo(console);
			

			if (inventory.size() / columns == 0) {

				for (unsigned int j = 0; j < inventory.size() ; j++) {

					inventory[j].setPosition(15 + j * 15 - inventory[j].getDimensions().X / 2,
											 console.getDimensions().Y / 2 - inventory[j].getDimensions().Y - 10);
					inventory[j].addTo(console);

				}
			}
			else {
				for (unsigned int i = 0; i < inventory.size() / columns; i++) {

					for (unsigned int j = 0; j < columns; j++) {
						int index = i * columns + j;

						inventory[index].setPosition(15 + j * 15 - inventory[index].getDimensions().X / 2,
													 console.getDimensions().Y / 2 + i * 15 - inventory[index].getDimensions().Y - 10);
						inventory[index].addTo(console);

					}

					if (i + 1 == inventory.size() / columns && inventory.size() % columns != 0) {
						for (unsigned int j = 0; j < inventory.size() % columns; j++) {
							int index = (i + 1) * columns + j;

							inventory[index].setPosition(15 + j * 15 - inventory[index].getDimensions().X / 2,
														 console.getDimensions().Y / 2 + (i + 1) * 15 - inventory[index].getDimensions().Y - 10);
							inventory[index].addTo(console);

						}
					}
				}
			}


			if (mouse.X > goForward.getPosition().X && mouse.X < goForward.getPosition().X + goForward.getDimensions().X &&
				mouse.Y > goForward.getPosition().Y && mouse.Y < goForward.getPosition().Y + goForward.getDimensions().Y) {
				goForward = Object("\n\n          NEXT          \n\n", YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {
					if(dedniel || saved) state = GAME_OVER;
					else state = SURVIVAL_RATION;

					Sleep(buttonWait);

					if (Input::isEvent(Events::Mouse_Left)) {}
					break;
				}
			}
			else {
				goForward = Object("\n\n          NEXT          \n\n", YELLOW | INTENSIFY | RED_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {}
			}

			goForward.setPosition(notebook.getPosition().X + notebook.getDimensions().X - goForward.getDimensions().X - 5,
								  notebook.getPosition().Y + notebook.getDimensions().Y - goForward.getDimensions().Y - 5);
			goForward.addTo(console);


			break;

		///////////////////////////////  2.2  Food Rationing   //////////////////////////////////////
		case SURVIVAL_RATION:
			if (Input::isEvent(Events::Escape)) {
				endGame = true;
				break;
			}

			dayHeading = Object("\n     DAY " + std::to_string(day) + "     \n", YELLOW | INTENSIFY | RED_BACK);
			
			notebookText = Object("Time to ration supplies...");

			dayHeading.setPosition(console.getDimensions().X / 2 - dayHeading.getDimensions().X / 2 + 8,
								   console.getDimensions().Y / 2 - dayHeading.getDimensions().Y / 2 - 50);
			notebookText.setPosition(notebook.getPosition().X + notebook.getDimensions().X / 2 - 45,
									 notebook.getPosition().Y + notebook.getDimensions().Y / 2 - notebookText.getDimensions().Y / 2 - 30);

			chrHeading.addTo(console);
			invHeading.addTo(console);
			
			notebook.addTo(console);
			dayHeading.addTo(console);
			notebookText.addTo(console);

			// Characters in HUD
			for (unsigned int i = 0; i < characters.size(); i++) {
				characters[i].setPosition(7 * console.getDimensions().X / 8 - characters[i].getDimensions().X / 2,
					console.getDimensions().Y / 2 + i * 20 - 20);
				characters[i].addTo(console);
			}
			
			// Characters in notebook
			for (unsigned int i = 0; i < characters.size(); i++) {
				characters[i].setPosition(notebook.getPosition().X + notebook.getDimensions().X / 2 - 45 + i * 25,
					notebook.getPosition().Y + notebook.getDimensions().Y / 2 - characters[i].getDimensions().Y / 2);
				characters[i].addTo(console);
				
				if (characters[i].isSick) {
					if (characters[i].hasMed) {
						medkits[0].setPosition(characters[i].getPosition().X + 4,
											   characters[i].getPosition().Y - 16);
					}
					else {
						medkits[0].setPosition(characters[i].getPosition().X + 4,
											   characters[i].getPosition().Y + characters[i].getDimensions().Y + 16);
					}
					medkits[0].addTo(console);
				}

				if (characters[i].hasFood) {
					soupCans[0].setPosition(characters[i].getPosition().X,
											characters[i].getPosition().Y - 8);
				}
				else {
					soupCans[0].setPosition(characters[i].getPosition().X,
											characters[i].getPosition().Y + characters[i].getDimensions().Y + 10);
				}
				soupCans[0].addTo(console);

				if (characters[i].hasWater) {
					waterBottles[0].setPosition(characters[i].getPosition().X + 8,
												characters[i].getPosition().Y - 10);
				}
				else {
					waterBottles[0].setPosition(characters[i].getPosition().X + 8,
												characters[i].getPosition().Y + characters[i].getDimensions().Y + 8);
				}

				waterBottles[0].addTo(console);

				if (mouse.X > characters[i].getPosition().X && mouse.X < characters[i].getPosition().X + characters[i].getDimensions().X &&
					mouse.Y > characters[i].getPosition().Y && mouse.Y < characters[i].getPosition().Y + characters[i].getDimensions().Y) {
					
					selectionBar = Object("                    ", WHITE_BACK | INTENSIFY_BACK);
					selectionBar.setPosition(characters[i].getPosition().X - 1,
											 characters[i].getPosition().Y + characters[i].getDimensions().Y + 1);
					
					if (Input::isEvent(Events::Mouse_Left)) {

						if (!characters[i].hasFood && characters[i].hasWater) {
							characters[i].hasFood = false;
							characters[i].hasWater = false;
							inventory.push_back(waterBottles[0]);
						}
						else if (!characters[i].hasWater && characters[i].hasFood) {
							characters[i].hasFood = false;
							characters[i].hasWater = false;
							inventory.push_back(soupCans[0]);
						}
						else {
							if (!characters[i].hasFood) {

								for (unsigned int j = 0; j < soupCans.size(); j++) {
									if (std::find(inventory.begin(), inventory.end(), soupCans[j]) != inventory.end()) {
										characters[i].hasFood = true;
										inventory.erase(std::find(inventory.begin(), inventory.end(), soupCans[j]));
										break;
									}
									else characters[i].hasFood = false;
								}
							}
							else {
								inventory.push_back(soupCans[0]);
								characters[i].hasFood = false;
							}

							if (!characters[i].hasWater) {
								for (unsigned int j = 0; j < waterBottles.size(); j++) {
									if (std::find(inventory.begin(), inventory.end(), waterBottles[j]) != inventory.end()) {
										inventory.erase(std::find(inventory.begin(), inventory.end(), waterBottles[j]));
										characters[i].hasWater = true;
										break;
									}
									else characters[i].hasWater = false;
								}
							}
							else {
								inventory.push_back(waterBottles[0]);
								characters[i].hasWater = false;
							}
						}

						Sleep(buttonWait);
						if (Input::isEvent(Events::Mouse_Left)) {}
						break;
					}
				}
				else if (mouse.X > soupCans[0].getPosition().X && mouse.X < soupCans[0].getPosition().X + soupCans[0].getDimensions().X &&
						 mouse.Y > soupCans[0].getPosition().Y && mouse.Y < soupCans[0].getPosition().Y + soupCans[0].getDimensions().Y) {
					selectionBar = Object("       ", WHITE_BACK | INTENSIFY_BACK);
					selectionBar.setPosition(soupCans[0].getPosition().X - 1,
											 soupCans[0].getPosition().Y + soupCans[0].getDimensions().Y + 1);

					if (Input::isEvent(Events::Mouse_Left)) {
						if (!characters[i].hasFood) {

							for (unsigned int j = 0; j < soupCans.size(); j++) {
								if (std::find(inventory.begin(), inventory.end(), soupCans[j]) != inventory.end()) {
									characters[i].hasFood = true;
									inventory.erase(std::find(inventory.begin(), inventory.end(), soupCans[j]));
									break;
								}
								else characters[i].hasFood = false;
							}
						}
						else {
							inventory.push_back(soupCans[0]);
							characters[i].hasFood = false;
						}

						Sleep(buttonWait);
						if (Input::isEvent(Events::Mouse_Left)) {}
						break;
					}

				}
				else if (mouse.X > waterBottles[0].getPosition().X && mouse.X < waterBottles[0].getPosition().X + waterBottles[0].getDimensions().X &&
						 mouse.Y > waterBottles[0].getPosition().Y && mouse.Y < waterBottles[0].getPosition().Y + waterBottles[0].getDimensions().Y) {
					selectionBar = Object("       ", WHITE_BACK | INTENSIFY_BACK);
					selectionBar.setPosition(waterBottles[0].getPosition().X - 1,
						waterBottles[0].getPosition().Y + waterBottles[0].getDimensions().Y + 1);

					if (Input::isEvent(Events::Mouse_Left)) {
						if (!characters[i].hasWater) {

							for (unsigned int j = 0; j < waterBottles.size(); j++) {
								if (std::find(inventory.begin(), inventory.end(), waterBottles[j]) != inventory.end()) {
									characters[i].hasWater = true;
									inventory.erase(std::find(inventory.begin(), inventory.end(), waterBottles[j]));
									break;
								}
								else characters[i].hasWater = false;
							}
						}
						else {
							inventory.push_back(waterBottles[0]);
							characters[i].hasWater = false;
						}

						Sleep(buttonWait);
						if (Input::isEvent(Events::Mouse_Left)) {}
						break;
					}

				}
				else if (mouse.X > medkits[0].getPosition().X && mouse.X < medkits[0].getPosition().X + medkits[0].getDimensions().X &&
						 mouse.Y > medkits[0].getPosition().Y && mouse.Y < medkits[0].getPosition().Y + medkits[0].getDimensions().Y) {
					selectionBar = Object("            ", WHITE_BACK | INTENSIFY_BACK);
					selectionBar.setPosition(medkits[0].getPosition().X - 1,
						medkits[0].getPosition().Y + medkits[0].getDimensions().Y + 1);

					if (Input::isEvent(Events::Mouse_Left)) {
						if (!characters[i].hasMed) {

							for (unsigned int j = 0; j < medkits.size(); j++) {
								if (std::find(inventory.begin(), inventory.end(), medkits[j]) != inventory.end()) {
									characters[i].hasMed = true;
									inventory.erase(std::find(inventory.begin(), inventory.end(), medkits[j]));
									break;
								}
								else characters[i].hasMed = false;
							}
						}
						else {
							inventory.push_back(medkits[0]);
							characters[i].hasMed = false;
						}

						Sleep(buttonWait);
						if (Input::isEvent(Events::Mouse_Left)) {}
						break;
					}

				}
				
				else {
					selectionBar = Object("");
					if (Input::isEvent(Events::Mouse_Left)) {}
				}
				selectionBar.addTo(console);
			}

			std::sort(inventory.begin(), inventory.end());

			if (inventory.size() / columns == 0) {

				for (unsigned int j = 0; j < inventory.size(); j++) {

					inventory[j].setPosition(15 + j * 15 - inventory[j].getDimensions().X / 2,
						console.getDimensions().Y / 2 - inventory[j].getDimensions().Y - 10);
					inventory[j].addTo(console);

				}
			}
			else {
				for (unsigned int i = 0; i < inventory.size() / columns; i++) {

					for (unsigned int j = 0; j < columns; j++) {
						int index = i * columns + j;

						inventory[index].setPosition(15 + j * 15 - inventory[index].getDimensions().X / 2,
							console.getDimensions().Y / 2 + i * 15 - inventory[index].getDimensions().Y - 10);
						inventory[index].addTo(console);

					}

					if (i + 1 == inventory.size() / columns && inventory.size() % columns != 0) {
						for (unsigned int j = 0; j < inventory.size() % columns; j++) {
							int index = (i + 1) * columns + j;

							inventory[index].setPosition(15 + j * 15 - inventory[index].getDimensions().X / 2,
								console.getDimensions().Y / 2 + (i + 1) * 15 - inventory[index].getDimensions().Y - 10);
							inventory[index].addTo(console);

						}
					}
				}
			}

			if (mouse.X > goBack.getPosition().X && mouse.X < goBack.getPosition().X + goBack.getDimensions().X &&
				mouse.Y > goBack.getPosition().Y && mouse.Y < goBack.getPosition().Y + goBack.getDimensions().Y) {
				goBack = Object("\n\n          BACK          \n\n", YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {
					state = SURVIVAL_STATUS;
					Sleep(buttonWait);
					if (Input::isEvent(Events::Mouse_Left)) {}
					break;
				}
			}
			else if (mouse.X > goForward.getPosition().X && mouse.X < goForward.getPosition().X + goForward.getDimensions().X &&
					 mouse.Y > goForward.getPosition().Y && mouse.Y < goForward.getPosition().Y + goForward.getDimensions().Y) {
				goForward = Object("\n\n          NEXT          \n\n", YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {
					state = SURVIVAL_EVENT;
					Sleep(buttonWait);
					if (Input::isEvent(Events::Mouse_Left)) {}
					break;
				}
			}
			else {
				goBack = Object("\n\n          BACK          \n\n", YELLOW | INTENSIFY | RED_BACK);
				goForward = Object("\n\n          NEXT          \n\n", YELLOW | INTENSIFY | RED_BACK);

				if (Input::isEvent(Events::Mouse_Left)) {}
			}

			goBack.setPosition(   notebook.getPosition().X + 25,
							      notebook.getPosition().Y + notebook.getDimensions().Y - goBack.getDimensions().Y - 5);
			goForward.setPosition(notebook.getPosition().X + notebook.getDimensions().X - goForward.getDimensions().X - 5,
								  notebook.getPosition().Y + notebook.getDimensions().Y - goForward.getDimensions().Y - 5);
			
			goBack.addTo(console);
			goForward.addTo(console);

			break;

		///////////////////////////////  2.3  RNG Events  //////////////////////////////////////
		case SURVIVAL_EVENT:
			if (Input::isEvent(Events::Escape)) {
				endGame = true;
				break;
			}
			
			dayHeading = Object("\n     DAY " + std::to_string(day) + "     \n", YELLOW | INTENSIFY | RED_BACK);
			
			notebookText = Object(survivalEvent);

			dayHeading.setPosition(console.getDimensions().X / 2 - dayHeading.getDimensions().X / 2 + 8,
								   console.getDimensions().Y / 2 - dayHeading.getDimensions().Y / 2 - 50);
			notebookText.setPosition(notebook.getPosition().X + notebook.getDimensions().X / 2 - 48,
									 notebook.getPosition().Y + notebook.getDimensions().Y / 2 - notebookText.getDimensions().Y / 2 - 30);

			chrHeading.addTo(console);
			invHeading.addTo(console);
			
			notebook.addTo(console);
			dayHeading.addTo(console);
			notebookText.addTo(console);


			for (unsigned int i = 0; i < characters.size(); i++) {
				characters[i].setPosition(7 * console.getDimensions().X / 8 - characters[i].getDimensions().X / 2,
					console.getDimensions().Y / 2 + i * 20 - 20);
				characters[i].addTo(console);
			}

			if (inventory.size() / columns == 0) {

				for (unsigned int j = 0; j < inventory.size(); j++) {

					inventory[j].setPosition(15 + j * 15 - inventory[j].getDimensions().X / 2,
						console.getDimensions().Y / 2 - inventory[j].getDimensions().Y - 10);
					inventory[j].addTo(console);

				}
			}
			else {
				for (unsigned int i = 0; i < inventory.size() / columns; i++) {

					for (unsigned int j = 0; j < columns; j++) {
						int index = i * columns + j;

						inventory[index].setPosition(15 + j * 15 - inventory[index].getDimensions().X / 2,
							console.getDimensions().Y / 2 + i * 15 - inventory[index].getDimensions().Y - 10);
						inventory[index].addTo(console);

					}

					if (i + 1 == inventory.size() / columns && inventory.size() % columns != 0) {
						for (unsigned int j = 0; j < inventory.size() % columns; j++) {
							int index = (i + 1) * columns + j;

							inventory[index].setPosition(15 + j * 15 - inventory[index].getDimensions().X / 2,
								console.getDimensions().Y / 2 + (i + 1) * 15 - inventory[index].getDimensions().Y - 10);
							inventory[index].addTo(console);

						}
					}
				}
			}

			if (gameEvent) {
				option1Button.setPosition(console.getDimensions().X / 2 - option1Button.getDimensions().X / 2 + 8,
					console.getDimensions().Y / 2 - option1Button.getDimensions().Y / 2 - 15);
				option1Button.addTo(console);
				
				if (mouse.X > option1Button.getPosition().X && mouse.X < option1Button.getPosition().X + option1Button.getDimensions().X &&
					mouse.Y > option1Button.getPosition().Y && mouse.Y < option1Button.getPosition().Y + option1Button.getDimensions().Y) {
					option1Button = Object(option1, YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
					if (Input::isEvent(Events::Mouse_Left)) {
						optionChosen = 0;
						Sleep(buttonWait);
						if (Input::isEvent(Events::Mouse_Left)) {}
						break;
					}
				}
				else if (optionChosen == 0) {
					option1Button = Object(option1, RED | YELLOW_BACK | INTENSIFY_BACK);
					if (Input::isEvent(Events::Mouse_Left)) {}
				}
				else {
					option1Button = Object(option1, YELLOW | INTENSIFY | RED_BACK);
					if (Input::isEvent(Events::Mouse_Left)) {}
				}


				if (option2 != "") {
					option2Button.setPosition(console.getDimensions().X / 2 - option1Button.getDimensions().X / 2 + 8,
						console.getDimensions().Y / 2 - option1Button.getDimensions().Y / 2 - 10);
					option2Button.addTo(console);

					if (mouse.X > option2Button.getPosition().X && mouse.X < option2Button.getPosition().X + option2Button.getDimensions().X &&
						mouse.Y > option2Button.getPosition().Y && mouse.Y < option2Button.getPosition().Y + option2Button.getDimensions().Y) {
						option2Button = Object(option2, YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {
							optionChosen = 1;
							Sleep(buttonWait);
							if (Input::isEvent(Events::Mouse_Left)) {}
							break;
						}
					}
					else if (optionChosen == 1) {
						option2Button = Object(option2, RED | YELLOW_BACK | INTENSIFY_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {}
					}
					else {
						option2Button = Object(option2, YELLOW | INTENSIFY | RED_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {}
					}
				}

				if (option3 != "") {
					option3Button.setPosition(console.getDimensions().X / 2 - option1Button.getDimensions().X / 2 + 8,
						console.getDimensions().Y / 2 - option1Button.getDimensions().Y / 2 - 5);
					option3Button.addTo(console);

					if (mouse.X > option3Button.getPosition().X && mouse.X < option3Button.getPosition().X + option3Button.getDimensions().X &&
						mouse.Y > option3Button.getPosition().Y && mouse.Y < option3Button.getPosition().Y + option3Button.getDimensions().Y) {
						option3Button = Object(option3, YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {
							optionChosen = 2;
							Sleep(buttonWait);
							if (Input::isEvent(Events::Mouse_Left)) {}
							break;
						}
					}
					else if (optionChosen == 2) {
						option3Button = Object(option3, RED | YELLOW_BACK | INTENSIFY_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {}
					}
					else {
						option3Button = Object(option3, YELLOW | INTENSIFY | RED_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {}
					}
				}

				if (option4 != "") {
					option4Button.setPosition(console.getDimensions().X / 2 - option1Button.getDimensions().X / 2 + 8,
						console.getDimensions().Y / 2 - option1Button.getDimensions().Y / 2);
					option4Button.addTo(console);

					if (mouse.X > option4Button.getPosition().X && mouse.X < option4Button.getPosition().X + option4Button.getDimensions().X &&
						mouse.Y > option4Button.getPosition().Y && mouse.Y < option4Button.getPosition().Y + option4Button.getDimensions().Y) {
						option4Button = Object(option4, YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {
							optionChosen = 3;
							Sleep(buttonWait);
							if (Input::isEvent(Events::Mouse_Left)) {}
							break;
						}
					}
					else if (optionChosen == 3) {
						option4Button = Object(option4, RED | YELLOW_BACK | INTENSIFY_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {}
					}
					else {
						option4Button = Object(option4, YELLOW | INTENSIFY | RED_BACK);
						if (Input::isEvent(Events::Mouse_Left)) {}
					}
				}
			}

			
			if (optionChosen != 100) {
				if (mouse.X > goForward.getPosition().X && mouse.X < goForward.getPosition().X + goForward.getDimensions().X &&
					mouse.Y > goForward.getPosition().Y && mouse.Y < goForward.getPosition().Y + goForward.getDimensions().Y) {
					goForward = Object("\n\n        NEXT DAY        \n\n", YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
					if (Input::isEvent(Events::Mouse_Left)) {
						state = SURVIVAL_NEW_DAY;
						Sleep(buttonWait);
						if (Input::isEvent(Events::Mouse_Left)) {}
						break;
					}
				}
				else {
					goForward = Object("\n\n        NEXT DAY        \n\n", YELLOW | INTENSIFY | RED_BACK);
					if (Input::isEvent(Events::Mouse_Left)) {}
				}

				goForward.setPosition(notebook.getPosition().X + notebook.getDimensions().X - goForward.getDimensions().X - 5,
									  notebook.getPosition().Y + notebook.getDimensions().Y - goForward.getDimensions().Y - 5);
				goForward.addTo(console);
			}
			
			
			if (mouse.X > goBack.getPosition().X && mouse.X < goBack.getPosition().X + goBack.getDimensions().X &&
				mouse.Y > goBack.getPosition().Y && mouse.Y < goBack.getPosition().Y + goBack.getDimensions().Y) {
				goBack = Object("\n\n          BACK          \n\n", YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {
					state = SURVIVAL_RATION;
					Sleep(buttonWait);
					if (Input::isEvent(Events::Mouse_Left)) {}
					break;
				}
			}
			else {
				goBack = Object("\n\n          BACK          \n\n", YELLOW | INTENSIFY | RED_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {}
			}
			
			goBack.setPosition(   notebook.getPosition().X + 25,
							      notebook.getPosition().Y + notebook.getDimensions().Y - goBack.getDimensions().Y - 5);
			
			goBack.addTo(console);

			break;

		///////////////////////////////   Game Over Screen   //////////////////////////////////////
		case GAME_OVER:
			goBack.setPosition(5, console.getDimensions().Y - goBack.getDimensions().Y - 3);
			goBack.addTo(console);

			if (mouse.X > goBack.getPosition().X && mouse.X < goBack.getPosition().X + goBack.getDimensions().X &&
				mouse.Y > goBack.getPosition().Y && mouse.Y < goBack.getPosition().Y + goBack.getDimensions().Y) {
				goBack = Object("\n\n\n              BACK TO MENU              \n\n\n", YELLOW | INTENSIFY | RED_BACK | INTENSIFY_BACK);
				if (Input::isEvent(Events::Mouse_Left)) {
					stopMusic();
					state = MAIN_MENU;
					Sleep(buttonWait);
					playMusic("audio/menu.wav");
					break;
				}
			}
			else {
				goBack = Object("\n\n\n              BACK TO MENU              \n\n\n", YELLOW | INTENSIFY | RED_BACK);

				if(Input::isEvent(Events::Mouse_Left)) {}
			}

			if (dedniel) {
				gameOverLose.setPosition(console.getDimensions().X / 2 - gameOverLose.getDimensions().X / 2,
										 console.getDimensions().Y / 2 - gameOverLose.getDimensions().Y / 2);
				gameOverLose.addTo(console);
			}
			else {
				gameOverWin.setPosition(console.getDimensions().X / 2 - gameOverWin.getDimensions().X / 2,
										 console.getDimensions().Y / 2 - gameOverWin.getDimensions().Y / 2);
				gameOverWin.addTo(console);
			}

			break;
		}
		
		do {
			end = Clock::now();
			duration = end - start;
			frameTime = duration.count() / 1000000000.0;
		} while (frameTime < 1.0 / FRAME_RATE);

		console.render();
	}


	///////////////////////////////   Game Exit Screen   //////////////////////////////////////
	console.clearBuffer();
	Object exitGame = Object("\n  EXITING GAME...  \n", RED | YELLOW_BACK | INTENSIFY_BACK);
	exitGame.setPosition(console.getDimensions().X / 2 - exitGame.getDimensions().X / 2,
						 console.getDimensions().Y / 2 - exitGame.getDimensions().Y / 2);
	exitGame.addTo(console);
	console.render();
	Sleep(2000);
	return 0;
}