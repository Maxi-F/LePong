#pragma once
#include "../entities/paddle.h";
#include "../entities/ball.h";
#include "../entities/powerUp.h";
#include "../entities/player.h";
#include "../screens.h";
#include "../timer.h";

struct GameplayCamera {
    Camera3D camera;
    int cameraMode;
};

struct GameplayEntities {
    Player players[2];
    Ball ball;
    PowerUp powerUp;
    Timer timerForPowerUp;
    GameplayCamera camera;
    bool isPaused;
};

void updateCamera(GameplayEntities& gameEntities);
void checkGameplayInputs(GameplayEntities* gameEntities, Screens& screen, bool& shouldClose);
GameplayEntities initGameplay(bool isAgainstCpu);
void updateCpuMovement(GameplayEntities* gameplayEntities);
void checkGameplayCollisions(GameplayEntities* gameEntities);
void drawGameplay(GameplayEntities gameEntities);
void updatePowerUp(GameplayEntities& gameEntities);
