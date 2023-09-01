#include "powerUp.h"
#include "../utils.h"
#include "../constants.h"
#include <iostream>

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
	const float Y_POSITION = GetRandomValue(-getHalf(FIELD_DIMENSIONS.y) + Y_MARGIN, getHalf(FIELD_DIMENSIONS.y) - HEIGHT - Y_MARGIN);
	const float X_POSITION = getRandomNegativeOrPositive() == 1 ? -FIELD_DIMENSIONS.x / 4 : FIELD_DIMENSIONS.x / 4;

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
	DrawCubeV(
		{
			powerUp.rectangle.x + getHalf(powerUp.rectangle.width),
			0,
			powerUp.rectangle.y + getHalf(powerUp.rectangle.height)
		}, {
			powerUp.rectangle.width,
			10.0f,
			powerUp.rectangle.height
		},
		RED
	);

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
