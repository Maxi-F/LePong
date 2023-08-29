#include "powerUp.h"
#include "utils.h"

void checkPowerUpCollision(PowerUp powerUp, Ball& ball, Paddle& paddle) {
	switch (powerUp.type) {
		case PowerUpType::ENLARGE:
			enlarge(paddle);
			break;
		case PowerUpType::REDUCE:
			reduce(paddle);
			break;
		case PowerUpType::PLUS_POINTS:
			addPoints(ball);
			break;
	}
}

bool isNotSetted(PowerUp powerUp) {
	return powerUp.type == PowerUpType::EMPTY;
}

static Rectangle generatePowerUpRectangle() {
	const float HEIGHT = 40.0f;
	const float WIDTH = 40.0f;
	const float Y_MARGIN = 30.0f;
	const float Y_POSITION = GetRandomValue(Y_MARGIN, GetScreenHeight() - HEIGHT - Y_MARGIN);
	const float X_POSITION = getRandomNegativeOrPositive() == 1 ? GetScreenWidth() / 4 : 3 * GetScreenWidth() / 4;

	return {
		X_POSITION,
		Y_POSITION,
		WIDTH,
		HEIGHT,
	};
}

void generateRandomPowerUp(PowerUp& powerUp) {
	PowerUpType powerUpType = (PowerUpType)GetRandomValue((int)PowerUpType::ENLARGE, (int)PowerUpType::PLUS_POINTS);

	Rectangle rectangle = generatePowerUpRectangle();

	switch (powerUpType) {
		case PowerUpType::ENLARGE:
			powerUp = {
				powerUpType,
				rectangle,
				"+"
			};
			break;
		case PowerUpType::REDUCE:
			powerUp = {
				powerUpType,
				rectangle,
				"-"
			};
			break;
		case PowerUpType::PLUS_POINTS:
			powerUp = {
				powerUpType,
				rectangle,
				"2"
			};
			break;
	};
}

void drawPowerUp(PowerUp powerUp) {
	DrawRectangleRec(powerUp.rectangle, RED);

	float FONT_SIZE = 10.0f;
	float textLength = MeasureText(powerUp.text, FONT_SIZE);

	DrawText(
		powerUp.text,
		powerUp.rectangle.x + getHalf(powerUp.rectangle.width) - getHalf(textLength),
		powerUp.rectangle.y + getHalf(powerUp.rectangle.height) - getHalf(FONT_SIZE),
		FONT_SIZE,
		WHITE
	);
}
