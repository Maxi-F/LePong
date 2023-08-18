#include "raylib.h"
#include "paddle.h"

void checkInput(Paddle& paddle) {
    if (IsKeyDown(paddle.keyUp) && paddle.rectangle.y >= 0) paddle.rectangle.y -= paddle.velocity;
    if (IsKeyDown(paddle.keyDown) && paddle.rectangle.y <= GetScreenHeight() - paddle.rectangle.height) paddle.rectangle.y += paddle.velocity;
};
