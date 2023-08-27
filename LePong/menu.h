#pragma once
#include <string>
#include "screens.h"
#include "game.h"
#include "gameplay.h"
#include "credits.h"

enum Option {
	PLAY,
	READ_CREDITS,
	EXIT,
	OPTIONS_QUANTITY
};

struct MenuOption {
	Option option;
	std::string text;
	bool isHovered;
	Rectangle optionBox;
};

struct Menu {
	MenuOption options[Option::OPTIONS_QUANTITY];
};

struct GameEntities {
	GameplayEntities gameplayEntities;
	Menu menu;
	CreditsScreen creditsScreen;
};

void drawMenu(Menu menu);
Menu initMenu();
void checkMenuInputAndCollision(Screens& screen, bool& shouldClose, Menu& menu, GameEntities& gameplayEntities);
