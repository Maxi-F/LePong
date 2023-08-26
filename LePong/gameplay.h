#pragma once
#include "paddle.h";
#include "ball.h";
#include "player.h";

struct GameEntities {
    Player players[2];
    Ball ball;
};

void checkGameplayInputs(GameEntities* gameEntities);
GameEntities initGameplay();
void checkGameplayCollisions(GameEntities* gameEntities);
void drawGameplay(GameEntities gameEntities);
