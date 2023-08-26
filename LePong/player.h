#pragma once
#include "paddle.h"

static struct Player {
    Paddle paddle;
    KeyboardKey keyUp;
    KeyboardKey keyDown;
    int score;
};

void checkInput(Player& player);
