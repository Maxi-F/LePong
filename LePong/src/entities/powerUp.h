#pragma once
#include "raylib.h"
#include "paddle.h"
#include "ball.h"

enum PowerUpType {
	ENLARGE = 0,
	REDUCE,
	PLUS_POINTS,
	ROTATE_CAMERA,
	EMPTY
};

struct PowerUp {
	PowerUpType type;
	Rectangle rectangle;
	Color color;
};

void checkPowerUpCollision(PowerUp powerUp, Ball& ball, Paddle& paddle, int& cameraMode);
bool isNotSetted(PowerUp powerUp);
void drawPowerUp(PowerUp powerUp);
void generateRandomPowerUp(PowerUp& powerUp);
