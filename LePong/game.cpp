#include "raylib.h";
#include "game.h";
#include "screens.h";

static GameEntities init() {
    Vector2 ScreenDimensions = { 640, 480 };

    InitWindow(ScreenDimensions.x, ScreenDimensions.y, "LePong");

    GameplayEntities gameplayEntities = initGameplay();
    Menu menu = initMenu();

    return { gameplayEntities, menu };
}

static void close() {
    CloseWindow();
}

static void update(Screens& screen, bool& shouldClose, GameEntities& gameEntities) {
    switch (screen) {
    case Screens::MENU:
        checkMenuInputAndCollision(screen, shouldClose, gameEntities.menu);
        break;
    case Screens::GAMEPLAY:
        checkGameplayInputs(&gameEntities.gameplayEntities);
        checkGameplayCollisions(&gameEntities.gameplayEntities);
        break;
    };
}

static void draw(Screens screen, GameEntities gameEntities) {
    BeginDrawing();
    GetFontDefault();

    switch (screen) {
    case Screens::MENU:
        drawMenu(gameEntities.menu);
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

    while (!WindowShouldClose() && !shouldClose)
    {
        update(screen, shouldClose, gameEntities);
        
        draw(screen, gameEntities);
    }

    close();
}
