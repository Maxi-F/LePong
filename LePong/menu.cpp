#include "raylib.h"
#include "utils.h"
#include "menu.h"
#include <iostream>
#include <string>

static const float OPTION_RECTANGLE_WIDTH = 300.0f;
static const float OPTION_RECTANGLE_HEIGHT = 50.0f;
static const float OPTION_FONT_SIZE = 20.0f;
static const float TOP_MARGIN = 200.0f;
static const float OPTION_RECTANGLE_MARGIN = 25.0f;
static const float OPTION_BOX_BORDER_WIDTH = 4.0f;

static void drawOptionBox(MenuOption option) {
	if (option.isHovered) {
		DrawRectangleRec(option.optionBox, PINK);

		Rectangle insideRectangle = {
			option.optionBox.x + OPTION_BOX_BORDER_WIDTH,
			option.optionBox.y + OPTION_BOX_BORDER_WIDTH,
			option.optionBox.width - OPTION_BOX_BORDER_WIDTH * 2,
			option.optionBox.height - OPTION_BOX_BORDER_WIDTH * 2,
		};

		DrawRectangleRec(insideRectangle, RED);
	}
	else {
		DrawRectangleRec(option.optionBox, RED);
	}
}

static void drawOptionText(float yPosition, const char* text) {
	float textLength = MeasureText(text, OPTION_FONT_SIZE);

	DrawText(
		text,
		getHalf(GetScreenWidth()) - getHalf(textLength),
		yPosition + getHalf(OPTION_RECTANGLE_HEIGHT) - getHalf(OPTION_FONT_SIZE),
		OPTION_FONT_SIZE,
		WHITE
	);
}

static std::string optionToText(Option option) {
	switch (option) {
		case Option::PLAY:
			return "play";
		case Option::EXIT:
			return "Exit";
	}
}

static void actionPerMenuOption(Option option, Screens& screen, bool& shouldClose) {
	switch (option) {
		case Option::PLAY:
			screen = Screens::GAMEPLAY;
			break;
		case Option::EXIT:
			shouldClose = true;
			break;
	}
}

Menu initMenu() {
	MenuOption menuOptions[Option::OPTIONS_QUANTITY];

	for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
		float yPosition = TOP_MARGIN + (OPTION_RECTANGLE_MARGIN + OPTION_RECTANGLE_HEIGHT) * i;

		Rectangle optionRectangle = {
		getHalf(GetScreenWidth()) - getHalf(OPTION_RECTANGLE_WIDTH),
		yPosition,
		OPTION_RECTANGLE_WIDTH,
		OPTION_RECTANGLE_HEIGHT
		};

		menuOptions[i] = {
			(Option)i,
			optionToText((Option)i),
			false,
			optionRectangle
		};
	}

	return { { menuOptions[0], menuOptions[1] } };
}

void drawMenu(Menu menu) {
	for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
		drawOptionBox(menu.options[i]);
		drawOptionText(menu.options[i].optionBox.y, menu.options[i].text.c_str());
	}
}

void checkMenuInputAndCollision(Screens& screen, bool& shouldClose, Menu& menu) {
	Vector2 mousePosition = GetMousePosition();

	for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
		if (checkPointToRectangleCollision(menu.options[i].optionBox, mousePosition)) {
			menu.options[i].isHovered = true;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				actionPerMenuOption(menu.options[i].option, screen, shouldClose);
			}
		}
		else {
			menu.options[i].isHovered = false;
		}
	};
}
