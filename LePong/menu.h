#pragma once
#include <string>
#include "screens.h"

enum Option {
	PLAY = 0,
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

void drawMenu(Menu menu);
Menu initMenu();
void checkMenuInputAndCollision(Screens& screen, bool& shouldClose, Menu& menu);
