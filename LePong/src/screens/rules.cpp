#include "rules.h"
#include "../utils.h"
#include "../constants.h"

static const float X_PADDING = 50.0f;
static const float Y_PADDING = 80.0f;
static const float TEXT_FONT_SIZE = 18.0f;
static const float TEXT_MARGIN_Y = 10.0f;

static void drawGoBackBox(RulesGoBackRectangle goBackBox) {
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

	Rectangle goBackBoxRectangle = goBackBox.rectangle;

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
}

void drawRuleText(const char* text, float yPosition) {
	DrawText(
		text,
		X_PADDING,
		yPosition,
		TEXT_FONT_SIZE,
		WHITE
	);
}

static struct PowerUpRule {
	const char* powerUp;
	Color powerUpColor;
	const char* description;
};

static void drawPowerUpRule(PowerUpRule rule, float yPosition) {
	float powerUpTextLength = MeasureText(rule.powerUp, TEXT_FONT_SIZE);

	DrawText(
		rule.powerUp,
		X_PADDING,
		yPosition,
		TEXT_FONT_SIZE,
		rule.powerUpColor
	);

	DrawText(
		rule.description,
		X_PADDING + powerUpTextLength + getHalf(TEXT_FONT_SIZE),
		yPosition,
		TEXT_FONT_SIZE,
		WHITE
	);
}

void drawRules(RulesScreen rulesScreen) {
	drawGoBackBox(rulesScreen.goBackRectangle);
	const int ELEMENTAL_RULES_LENGTH = 3;
	const float MARGIN = (TEXT_FONT_SIZE + TEXT_MARGIN_Y);

	const char* rules[ELEMENTAL_RULES_LENGTH] = {
		"First player to 5 points wins.",
		"Player 1 (LEFT) moves with W (up) and S (down) keys.",
		"Player 2 (RIGHT) moves with Up Arrow and Down Arrow keys."
	};

	for (int i = 0; i < ELEMENTAL_RULES_LENGTH; i++) {
		drawRuleText(rules[i], Y_PADDING + (i * MARGIN));
	};

	float powerUpMargin = MARGIN;

	drawRuleText("In the game, power ups will be appearing:", Y_PADDING + powerUpMargin + ELEMENTAL_RULES_LENGTH * MARGIN);

	const int POWER_UP_RULES_LENGTH = 4;
	PowerUpRule powerUpRules[POWER_UP_RULES_LENGTH] = {
		{
			"GREEN",
			DARKGREEN,
			"Power up will enlarge your paddle."
		}, {
			"RED",
			RED,
			"Power up will reduce your paddle."
		}, {
			"PURPLE",
			DARKPURPLE,
			"Power up will make the point be plus two instead of plus one."
		}, {
			"GOLD",
			GOLD,
			"Power up is a special one!"
		}
	};

	for (int i = 0; i < POWER_UP_RULES_LENGTH; i++) {
		drawPowerUpRule(powerUpRules[i], Y_PADDING + powerUpMargin + ((i + ELEMENTAL_RULES_LENGTH + 1) * MARGIN));
	}
};

RulesScreen initRules() {
	const float GO_BACK_BOX_WIDTH = 100.0f;
	const float GO_BACK_BOX_HEIGHT = 50.0f;

	Rectangle goBackBoxRectangle = {
		X_PADDING,
		GetScreenHeight() - Y_PADDING,
		GO_BACK_BOX_WIDTH,
		GO_BACK_BOX_HEIGHT,
	};

	return { goBackBoxRectangle, false };
};

void checkRulesInputCollision(Screens& screen, RulesScreen& rules) {
	Vector2 mousePosition = GetMousePosition();

	if (checkPointToRectangleCollision(rules.goBackRectangle.rectangle, mousePosition)) {
		rules.goBackRectangle.isHovered = true;

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			screen = Screens::MENU;
		};
	}
	else {
		rules.goBackRectangle.isHovered = false;
	}
};

