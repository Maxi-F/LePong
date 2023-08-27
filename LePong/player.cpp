#include "raylib.h"
#include "player.h"
#include "ball.h"
#include "constants.h"

void checkInput(Player& player) {
	if (!player.isCpu) {
		if (IsKeyDown(player.keyUp) && isPaddleNotOnTop(player.paddle)) moveUp(player.paddle);
		if (IsKeyDown(player.keyDown) && isPaddleNotOnBottom(player.paddle)) moveDown(player.paddle);
	}
}

bool playerHasWon(Player player) {
	return player.score >= MAX_SCORE;
}

void updateCpuPlayerMovement(Player& player, Ball ball) {
	if (player.isCpu) {
		updatePaddlePositionPerBall(player.paddle, ball);
	}
}
