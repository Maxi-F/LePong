#include "powerUp.h"
#include "../utils.h"
#include "../constants.h"
#include <iostream>

void checkPowerUpCollision(PowerUp powerUp, Ball& ball, Paddle& paddle, int& cameraMode) {
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
		case PowerUpType::ROTATE_CAMERA:
			cameraMode = CAMERA_ORBITAL;
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
	PowerUpType powerUpType = (PowerUpType)GetRandomValue((int)PowerUpType::ENLARGE, (int)PowerUpType::ROTATE_CAMERA);

	Rectangle rectangle = generatePowerUpRectangle();

	switch (powerUpType) {
		case PowerUpType::ENLARGE:
			powerUp = {
				powerUpType,
				rectangle,
				DARKGREEN
			};
			break;
		case PowerUpType::REDUCE:
			powerUp = {
				powerUpType,
				rectangle,
				RED
			};
			break;
		case PowerUpType::PLUS_POINTS:
			powerUp = {
				powerUpType,
				rectangle,
				DARKPURPLE
			};
			break;
		case PowerUpType::ROTATE_CAMERA:
			powerUp = {
				powerUpType,
				rectangle,
				GOLD
			};
			break;
	};
}

void drawPowerUp(PowerUp powerUp) {
	float POWER_UP_HEIGHT = 10.0f;

	DrawCubeV(
		{
			powerUp.rectangle.x + getHalf(powerUp.rectangle.width),
			getHalf(POWER_UP_HEIGHT) + 1.0f,
			powerUp.rectangle.y + getHalf(powerUp.rectangle.height)
		}, {
			powerUp.rectangle.width,
			POWER_UP_HEIGHT,
			powerUp.rectangle.height
		},
		powerUp.color
	);
}
