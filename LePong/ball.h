#include "raylib.h"

struct Ball {
    Vector2 position;
    Vector2 direction;
    float velocity;
    float radius;
};

bool isBallOnLeftEdge(Ball& ball);
bool isBallOnRightEdge(Ball& ball);
void checkCollissionWith(Paddle paddle, Ball& ball);
void refreshVelocity(Ball& ball);
void refreshPosition(Ball& ball);
void refreshToInitialPosition(Ball& ball);
