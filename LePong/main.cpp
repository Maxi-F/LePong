#include "game.h"

int main()
{
    GameEntities gameEntities = init();

    // Loop
    while (!WindowShouldClose())
    {
        checkInputs(&gameEntities);

        checkCollisions(&gameEntities);

        draw(gameEntities);
    }

    // Cierre
    close();
}
