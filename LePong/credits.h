#pragma once
#include "raylib.h"
#include <string>
#include "screens.h"

#define CREDITS_SECTIONS 1

struct Credits {
	std::string title;
	std::string names;
};

struct GoBackRectangle {
	Rectangle rectangle;
	bool isHovered;
};

struct CreditsScreen {
	Credits credits[CREDITS_SECTIONS];
	GoBackRectangle goBackBox;
};

void drawCredits(CreditsScreen creditsScreen);
CreditsScreen initCredits();
void checkCreditsInputCollision(Screens& screen, CreditsScreen& credits);
