#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "utils.h"
#include <iostream>
using namespace std;

extern const Vector2 PADDLE_SIZE = { 15.0f, 80.0f };
extern const float PADDLE_MARGIN = 40.0f;
extern const float PADDLE_VELOCITY = 400.0f;

void moveUp(Paddle& paddle) {
    paddle.rectangle.y -= getWithFrameTime(paddle.velocity);
}

void enlarge(Paddle& paddle) {
    paddle.rectangle = {
        paddle.rectangle.x,
        paddle.rectangle.y,
        paddle.rectangle.width,
        PADDLE_SIZE.y + 40.0f
    };
}

void reduce(Paddle& paddle) {
    paddle.rectangle = {
        paddle.rectangle.x,
        paddle.rectangle.y,
        paddle.rectangle.width,
        PADDLE_SIZE.y - 20.0f
    };
}

void resetPaddle(Paddle& paddle) {
    paddle.rectangle = {
        paddle.rectangle.x,
        paddle.rectangle.y,
        paddle.rectangle.width,
        PADDLE_SIZE.y
   };
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
