#include "game.h"

int main()
{
    // Inicializaci�n
    GameEntities gameEntities = init();

    // Loop
    while (!WindowShouldClose())
    {
        // Chequeo de Input

        checkInputs(&gameEntities);

        // Actualizaci�n

        checkCollisions(&gameEntities);

        // Dibujado
        draw(gameEntities);
    }

    // Cierre
    close();
}
