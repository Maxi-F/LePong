#pragma once
#include "paddle.h";
#include "ball.h";
#include "player.h";

struct GameplayEntities {
    Player players[2];
    Ball ball;
};

void checkGameplayInputs(GameplayEntities* gameEntities);
GameplayEntities initGameplay();
void checkGameplayCollisions(GameplayEntities* gameEntities);
void drawGameplay(GameplayEntities gameEntities);
