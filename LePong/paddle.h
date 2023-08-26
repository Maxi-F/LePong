#pragma once
#include "raylib.h"

struct Paddle {
    Rectangle rectangle;
    int velocity;
};

extern const Vector2 PADDLE_SIZE;
extern const float PADDLE_MARGIN;
extern const float PADDLE_VELOCITY;

void moveUp(Paddle& paddle);

void moveDown(Paddle& paddle);

bool isPaddleNotOnTop(Paddle paddle);

bool isPaddleNotOnBottom(Paddle paddle);

void drawPaddle(Paddle paddle);

