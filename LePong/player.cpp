#include "raylib.h"
#include "player.h"
#include "paddle.h"

void checkInput(Player& player) {
	if (IsKeyDown(player.keyUp) && isPaddleNotOnTop(player.paddle)) moveUp(player.paddle);
	if (IsKeyDown(player.keyDown) && isPaddleNotOnBottom(player.paddle)) moveDown(player.paddle);
}
