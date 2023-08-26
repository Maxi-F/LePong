#include "raylib.h"
#include "paddle.h"
#include "utils.h"

extern const Vector2 PADDLE_SIZE = { 5.0f, 120.0f };
extern const float PADDLE_MARGIN = 40.0f;
extern const float PADDLE_VELOCITY = 400.0f;

void moveUp(Paddle& paddle) {
    paddle.rectangle.y -= getWithFrameTime(paddle.velocity);
}

void moveDown(Paddle& paddle) {
    paddle.rectangle.y += getWithFrameTime(paddle.velocity);
}

bool isPaddleNotOnTop(Paddle paddle) {
    return paddle.rectangle.y >= 0;
}

bool isPaddleNotOnBottom(Paddle paddle) {
    return paddle.rectangle.y <= GetScreenHeight() - paddle.rectangle.height;
}

void drawPaddle(Paddle paddle) {
    DrawRectangleRec(paddle.rectangle, PINK);
}
