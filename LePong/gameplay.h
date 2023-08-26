#pragma once
#include "paddle.h";
#include "ball.h";
#include "player.h";
#include "screens.h";

struct GameplayEntities {
    Player players[2];
    Ball ball;
};

void checkGameplayInputs(GameplayEntities* gameEntities, Screens& screen);
GameplayEntities initGameplay();
void checkGameplayCollisions(GameplayEntities* gameEntities);
void drawGameplay(GameplayEntities gameEntities);
