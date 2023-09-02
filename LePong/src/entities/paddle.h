#pragma once
#include "raylib.h"

struct Ball;

struct Paddle {
    Rectangle rectangle;
    float velocity;
    Color color;
    Color wiresColor;
};

extern const Vector2 PADDLE_SIZE;
extern const float PADDLE_MARGIN;
extern const float PADDLE_VELOCITY;

Paddle initPaddle(float position, Color color, Color wiresColor);

void moveUp(Paddle& paddle);

void moveDown(Paddle& paddle);

void enlarge(Paddle& paddle);

void reduce(Paddle& paddle);

bool isPaddleNotOnTop(Paddle paddle);

void resetPaddle(Paddle& paddle);

bool isPaddleNotOnBottom(Paddle paddle);

void drawPaddle(Paddle paddle);

void updatePaddlePositionPerBall(Paddle& paddle, Ball ball);
