#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "../utils.h"
#include "../constants.h"
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
    return paddle.rectangle.y >= -getHalf(FIELD_DIMENSIONS.y);
}

bool isPaddleNotOnBottom(Paddle paddle) {
    return paddle.rectangle.y <= getHalf(FIELD_DIMENSIONS.y) - paddle.rectangle.height;
}

void drawPaddle(Paddle paddle) {
    DrawCubeV(
        {
            paddle.rectangle.x + getHalf(paddle.rectangle.width),
            0,
            paddle.rectangle.y + getHalf(paddle.rectangle.height)
        }, {
            paddle.rectangle.width,
            10.0f,
            paddle.rectangle.height
        },
        PINK
    );

    DrawCubeWiresV(
        {
            paddle.rectangle.x + getHalf(paddle.rectangle.width),
            0,
            paddle.rectangle.y + getHalf(paddle.rectangle.height)
        }, {
            paddle.rectangle.width,
            10.0f,
            paddle.rectangle.height
        },
        RED
    );
}

void updatePaddlePositionPerBall(Paddle& paddle, Ball ball) {
    float quarterPaddlePosition = paddle.rectangle.y + (paddle.rectangle.height / 4.0f);
    float threeQuartersPaddlePosition = paddle.rectangle.y + ( paddle.rectangle.height * 3.0f / 4.0f);

    if (isPaddleNotOnTop(paddle) && ball.position.z <= quarterPaddlePosition) moveUp(paddle);
    if (isPaddleNotOnBottom(paddle) && ball.position.z >= threeQuartersPaddlePosition) moveDown(paddle);
}
