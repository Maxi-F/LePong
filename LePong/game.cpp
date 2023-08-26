#include "raylib.h";
#include "gameplay.h";

static enum Screens {
    GAMEPLAY = 0,
    MENU = 1
};

static GameEntities init() {
    Vector2 ScreenDimensions = { 640, 480 };

    InitWindow(ScreenDimensions.x, ScreenDimensions.y, "LePong");

    return initGameplay();
}

static void close() {
    CloseWindow();
}

static void update(Screens screen, GameEntities& gameEntities) {
    switch (screen) {
    case Screens::MENU:
        break;
    case Screens::GAMEPLAY:
        checkGameplayInputs(&gameEntities);
        checkGameplayCollisions(&gameEntities);
        break;
    };
}

static void draw(Screens screen, GameEntities gameEntities) {
    BeginDrawing();
    switch (screen) {
    case Screens::MENU:
        break;
    case Screens::GAMEPLAY:
        drawGameplay(gameEntities);
        break;
    };
    EndDrawing();
}

void executeGameLoop() {
    GameEntities gameEntities = init();
    Screens screen = Screens::GAMEPLAY;

    while (!WindowShouldClose())
    {
        update(screen, gameEntities);
        
        draw(screen, gameEntities);
    }

    close();
}
