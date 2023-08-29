#pragma once
#include "paddle.h";
#include "ball.h";
#include "powerUp.h";
#include "player.h";
#include "screens.h";
#include "timer.h";

struct GameplayEntities {
    Player players[2];
    Ball ball;
    PowerUp powerUp;
    Timer timerForPowerUp;
};

void checkGameplayInputs(GameplayEntities* gameEntities, Screens& screen);
GameplayEntities initGameplay(bool isAgainstCpu);
void updateCpuMovement(GameplayEntities* gameplayEntities);
void checkGameplayCollisions(GameplayEntities* gameEntities);
void drawGameplay(GameplayEntities gameEntities);
void updatePowerUp(GameplayEntities& gameEntities);
