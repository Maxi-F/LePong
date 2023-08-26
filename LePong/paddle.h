#include "raylib.h"

struct Paddle {
    Rectangle rectangle;
    KeyboardKey keyUp;
    KeyboardKey keyDown;
    int velocity;
};

void checkInput(Paddle& paddle);
