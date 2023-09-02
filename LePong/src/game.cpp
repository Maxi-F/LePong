#include "raylib.h";
#include "game.h";
#include "screens/menu.h";
#include "screens.h";
#include "constants.h";

static GameEntities init() {
    InitWindow(SCREEN_DIMENSIONS.x, SCREEN_DIMENSIONS.y, "LePong");

    Menu menu = initMenu();

    return { {}, menu, {} };
}

static void close() {
    CloseWindow(); 
}

static void update(Screens& screen, bool& shouldClose, GameEntities& gameEntities) {
    switch (screen) {
    case Screens::MENU:
        checkMenuInputAndCollision(screen, shouldClose, gameEntities.menu, gameEntities);
        break;
    case Screens::CREDITS:
        checkCreditsInputCollision(screen, gameEntities.creditsScreen);
        break;
    case Screens::GAMEPLAY:
        checkGameplayInputs(&gameEntities.gameplayEntities, screen, shouldClose);
        updateCpuMovement(&gameEntities.gameplayEntities);
        updatePowerUp(gameEntities.gameplayEntities);
        updateCamera(gameEntities.gameplayEntities);
        checkGameplayCollisions(&gameEntities.gameplayEntities);
        break;
    };
}

static void draw(Screens screen, GameEntities gameEntities) {
    BeginDrawing();
    GetFontDefault();
    ClearBackground(BLACK);

    switch (screen) {
    case Screens::MENU:
        drawMenu(gameEntities.menu);
        break;
    case Screens::CREDITS:
        drawCredits(gameEntities.creditsScreen);
        break;
    case Screens::GAMEPLAY:
        drawGameplay(gameEntities.gameplayEntities);
        break;
    };
    
    EndDrawing();
}

void executeGameLoop() {
    GameEntities gameEntities = init();
    Screens screen = Screens::MENU;
    bool shouldClose = false;

    SetExitKey(0);

    while (!shouldClose)
    {
        update(screen, shouldClose, gameEntities);
        
        draw(screen, gameEntities);
    }

    close();
}
