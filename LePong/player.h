#pragma once
#include "paddle.h"
#include <string>

static struct Player {
    Paddle paddle;
    KeyboardKey keyUp;
    KeyboardKey keyDown;
    std::string name;
    int score;
};

void checkInput(Player& player);
bool playerHasWon(Player player);
