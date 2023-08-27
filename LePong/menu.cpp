#include "raylib.h"
#include "utils.h"
#include "menu.h"
#include "game.h"
#include "constants.h"
#include <iostream>
#include <string>

static const float OPTION_RECTANGLE_WIDTH = 300.0f;
static const float OPTION_RECTANGLE_HEIGHT = 50.0f;
static const float OPTION_FONT_SIZE = 20.0f;
static const float TOP_MARGIN = 150.0f;
static const float OPTION_RECTANGLE_MARGIN = 25.0f;
static const float TITLE_TOP_MARGIN = 40.0f;
static const float TITLE_FONT_SIZE = 50.0f;

static void drawOptionBox(MenuOption option) {
	if (option.isHovered) {
		DrawRectangleRec(option.optionBox, PINK);

		Rectangle insideRectangle = {
			option.optionBox.x + BOX_BORDER_WIDTH,
			option.optionBox.y + BOX_BORDER_WIDTH,
			option.optionBox.width - BOX_BORDER_WIDTH * 2,
			option.optionBox.height - BOX_BORDER_WIDTH * 2,
		};

		DrawRectangleRec(insideRectangle, IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? FOCUS_COLOR : RED);
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
		case Option::PLAY_PVP:
			return "Player vs Player";
		case Option::PLAY_CPU:
			return "Player vs CPU";
		case Option::EXIT:
			return "Exit";
		case Option::READ_CREDITS:
			return "Credits";
	}
}

static void actionPerMenuOption(Option option, Screens& screen, bool& shouldClose, GameEntities& gameplayEntities) {
	switch (option) {
		case Option::PLAY_PVP:
		case Option::PLAY_CPU:
			screen = Screens::GAMEPLAY;
			gameplayEntities.gameplayEntities = initGameplay(option == Option::PLAY_CPU);
			break;
		case Option::READ_CREDITS:
			screen = Screens::CREDITS;
			gameplayEntities.creditsScreen = initCredits();
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

	return { { menuOptions[0], menuOptions[1], menuOptions[2], menuOptions[3] } };
}

void drawMenu(Menu menu) {
	const char* title = "LePong";
	float titleLenght = MeasureText(title, TITLE_FONT_SIZE);

	DrawText("LePong", getHalf(GetScreenWidth()) - getHalf(titleLenght), TITLE_TOP_MARGIN, TITLE_FONT_SIZE, WHITE);

	for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
		drawOptionBox(menu.options[i]);
		drawOptionText(menu.options[i].optionBox.y, menu.options[i].text.c_str());
	}
}

void checkMenuInputAndCollision(Screens& screen, bool& shouldClose, Menu& menu, GameEntities& gameEntities) {
	Vector2 mousePosition = GetMousePosition();

	for (int i = 0; i < Option::OPTIONS_QUANTITY; i++) {
		if (checkPointToRectangleCollision(menu.options[i].optionBox, mousePosition)) {
			menu.options[i].isHovered = true;

			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				actionPerMenuOption(menu.options[i].option, screen, shouldClose, gameEntities);
			}
		}
		else {
			menu.options[i].isHovered = false;
		}
	};
}
