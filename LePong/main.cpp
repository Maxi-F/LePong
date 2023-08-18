#include "game.h"

int main()
{
    // Inicialización
    GameEntities gameEntities = init();

    // Loop
    while (!WindowShouldClose())
    {
        // Chequeo de Input

        checkInputs(&gameEntities);

        // Actualización

        checkCollisions(&gameEntities);

        // Dibujado
        draw(gameEntities);
    }

    // Cierre
    close();
}
