#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "utils.h"
#include <iostream>
using namespace std;

extern const Vector2 PADDLE_SIZE = { 5.0f, 80.0f };
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

void updatePaddlePositionPerBall(Paddle& paddle, Ball ball) {
    float quarterPaddlePosition = paddle.rectangle.y + (paddle.rectangle.height / 4.0f);
    float threeQuartersPaddlePosition = paddle.rectangle.y + ( paddle.rectangle.height * 3.0f / 4.0f);

    if (isPaddleNotOnTop(paddle) && ball.position.y <= quarterPaddlePosition) moveUp(paddle);
    if (isPaddleNotOnBottom(paddle) && ball.position.y >= threeQuartersPaddlePosition) moveDown(paddle);
}
