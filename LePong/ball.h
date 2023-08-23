#include "raylib.h"

struct Ball {
    Vector2 position;
    Vector2 velocity;
    float radius;
};

void checkCollissionWith(Paddle paddle, Ball& ball);
void refreshVelocity(Ball& ball);
void refreshPosition(Ball& ball);
Rectangle getCollisionBox(Ball ball);
