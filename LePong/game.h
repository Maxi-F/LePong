#pragma once
#include "gameplay.h"
#include "menu.h"

struct GameEntities {
	GameplayEntities gameplayEntities;
	Menu menu;
};

void executeGameLoop();
