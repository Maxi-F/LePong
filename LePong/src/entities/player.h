#pragma once
#include "paddle.h"
#include <string>

struct Ball;

static struct Player {
    Paddle paddle;
    KeyboardKey keyUp;
    KeyboardKey keyDown;
    std::string name;
    bool isCpu;
    int score;
};

void checkInput(Player& player);
bool playerHasWon(Player player);
void updateCpuPlayerMovement(Player& player, Ball ball);
