#pragma once
#include "raylib.h"
#include "../screens.h"

static struct RulesGoBackRectangle {
	Rectangle rectangle;
	bool isHovered;
};

struct RulesScreen {
	RulesGoBackRectangle goBackRectangle;
};

void drawRules(RulesScreen rulesScreen);
RulesScreen initRules();
void checkRulesInputCollision(Screens& screen, RulesScreen& rules);
