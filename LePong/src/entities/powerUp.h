#pragma once
#include "raylib.h"
#include "paddle.h"
#include "ball.h"

enum PowerUpType {
	ENLARGE = 0,
	REDUCE,
	PLUS_POINTS,
	EMPTY
};

struct PowerUp {
	PowerUpType type;
	Rectangle rectangle;
	const char* text;
};

void checkPowerUpCollision(PowerUp powerUp, Ball& ball, Paddle& paddle);
bool isNotSetted(PowerUp powerUp);
void drawPowerUp(PowerUp powerUp);
void generateRandomPowerUp(PowerUp& powerUp);
