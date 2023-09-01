#include "credits.h"
#include "raylib.h"
#include "../utils.h"
#include "../constants.h"
#include "../screens.h"

static const float X_PADDING = 50.0f;
static const float Y_PADDING = 80.0f;

static void drawGoBackBox(GoBackRectangle goBackBox) {
	if (goBackBox.isHovered) {
		DrawRectangleRec(goBackBox.rectangle, PINK);

		Rectangle insideRectangle = {
			goBackBox.rectangle.x + BOX_BORDER_WIDTH,
			goBackBox.rectangle.y + BOX_BORDER_WIDTH,
			goBackBox.rectangle.width - BOX_BORDER_WIDTH * 2,
			goBackBox.rectangle.height - BOX_BORDER_WIDTH * 2,
		};

		DrawRectangleRec(insideRectangle, IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? FOCUS_COLOR : RED);
	}
	else {
		DrawRectangleRec(goBackBox.rectangle, RED);
	}
}

void drawCredits(CreditsScreen creditsScreen) {
	const float CREDIT_TITLE_FONT_SIZE = 40.0f;
	const float CREDIT_SIZE = 30.0f;
	const float TITLE_TO_CREDIT_MARGIN = 20.0f;

	for (int i = 0; i < CREDITS_SECTIONS; i++) {
		const char* creditTitle = creditsScreen.credits[i].title.c_str();
		const char* credits = creditsScreen.credits[i].names.c_str();

		float titleLength = MeasureText(creditTitle, CREDIT_TITLE_FONT_SIZE);
		float creditLength = MeasureText(credits, CREDIT_SIZE);

		DrawText(
			creditTitle,
			getHalf(GetScreenWidth()) - getHalf(titleLength),
			Y_PADDING,
			CREDIT_TITLE_FONT_SIZE,
			RED
		);

		DrawText(
			credits,
			getHalf(GetScreenWidth()) - getHalf(creditLength),
			Y_PADDING + CREDIT_TITLE_FONT_SIZE + TITLE_TO_CREDIT_MARGIN,
			CREDIT_SIZE,
			WHITE
		);
	};

	Rectangle goBackBoxRectangle = creditsScreen.goBackBox.rectangle;

	drawGoBackBox(creditsScreen.goBackBox);

	const char* goBackText = "Go Back";
	const float GO_BACK_FONT_SIZE = 20.0f;

	float goBackLength = MeasureText(goBackText, GO_BACK_FONT_SIZE);

	DrawText(
		goBackText,
		goBackBoxRectangle.x + getHalf(goBackBoxRectangle.width) - getHalf(goBackLength),
		goBackBoxRectangle.y + getHalf(goBackBoxRectangle.height) - getHalf(GO_BACK_FONT_SIZE),
		GO_BACK_FONT_SIZE,
		WHITE
	);
};

void checkCreditsInputCollision(Screens& screen, CreditsScreen& credits) {
	Vector2 mousePosition = GetMousePosition();

	if (checkPointToRectangleCollision(credits.goBackBox.rectangle, mousePosition)) {
		credits.goBackBox.isHovered = true;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			screen = Screens::MENU;
		};
	}
	else {
		credits.goBackBox.isHovered = false;
	}
}

CreditsScreen initCredits() {
	Credits credits = {
		"DEVELOPERS",
		"Maximiliano Feldman"
	};

	const float GO_BACK_BOX_WIDTH = 100.0f;
	const float GO_BACK_BOX_HEIGHT = 50.0f;

	Rectangle goBackBoxRectangle = {
		X_PADDING,
		GetScreenHeight() - Y_PADDING,
		GO_BACK_BOX_WIDTH,
		GO_BACK_BOX_HEIGHT,
	};

	return {
		{ credits },
		{ goBackBoxRectangle, false } 
	};
}
