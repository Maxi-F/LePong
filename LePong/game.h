#include "paddle.h"
#include "ball.h"

struct GameEntities {
    Paddle paddles[2];
    Ball ball;
};

void checkInputs(GameEntities* gameEntities);
GameEntities init();
void checkCollisions(GameEntities* gameEntities);
void draw(GameEntities gameEntities);
void close();
