#pragma once
#include "raylib.h"

struct Ball {
    Vector2 position;
    Vector2 direction;
    float velocity;
    float radius;
};

extern const float BALL_RADIUS;
extern const float BALL_VELOCITY;
extern const float BALL_ACCELERATION;
extern const float MAX_BALL_ACCELERATION;

bool isBallOnLeftEdge(Ball& ball);
bool isBallOnRightEdge(Ball& ball);
void checkCollissionWith(Paddle paddle, Ball& ball);
void refreshVelocity(Ball& ball);
void refreshPosition(Ball& ball);
void refreshToInitialPosition(Ball& ball);
void drawBall(Ball ball);
