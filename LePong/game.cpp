#include "raylib.h";
#include "game.h";
#include "utils.h";
#include "constants.h";

void checkInputs(GameEntities* gameEntities) {
    for (int i = 0; i < 2; i++) {
        checkInput(gameEntities->paddles[i]);
    }
}

GameEntities init() {
    Vector2 ScreenDimensions = { 640, 480 };

    InitWindow(ScreenDimensions.x, ScreenDimensions.y, "LePong");

    int halfScreenWidth = getHalf(GetScreenWidth());
    int halfScreenHeight = getHalf(GetScreenHeight());

    Vector2 initialBallPosition = { halfScreenWidth, halfScreenHeight };

    Ball ball = {
        initialBallPosition,
        BALL_VELOCITY,
        BALL_RADIUS
    };

    Paddle player1 = {
        { PADDLE_MARGIN, halfScreenHeight - getHalf(PADDLE_SIZE.y), PADDLE_SIZE.x, PADDLE_SIZE.y },
        KEY_W,
        KEY_S,
        PADDLE_VELOCITY,
    };

    Paddle player2 = {
        { GetScreenWidth() - PADDLE_MARGIN, halfScreenHeight - getHalf(PADDLE_SIZE.y), PADDLE_SIZE.x, PADDLE_SIZE.y },
        KEY_UP,
        KEY_DOWN,
        PADDLE_VELOCITY,
    };

    return { {player1, player2}, ball };
}

void checkCollisions(GameEntities* gameEntities) {
    checkCollissionWith(gameEntities->paddles[0], gameEntities->ball);
    checkCollissionWith(gameEntities->paddles[1], gameEntities->ball);
    refreshPosition(gameEntities->ball);
    refreshVelocity(gameEntities->ball);
}

void draw(GameEntities gameEntities) {
    BeginDrawing();
    ClearBackground(BLACK); // system("cls");

    DrawCircleV(gameEntities.ball.position, gameEntities.ball.radius, WHITE);
    DrawRectangleRec(gameEntities.paddles[0].rectangle, PINK);
    DrawRectangleRec(gameEntities.paddles[1].rectangle, PINK);

    EndDrawing();
}

void close() {
    CloseWindow();
}
