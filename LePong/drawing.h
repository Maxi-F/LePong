#pragma once
#include "game.h"

enum Screens {
    GAMEPLAY = 0,
    MENU = 1
};

void draw(Screens& screen, GameEntities gameEntities);
