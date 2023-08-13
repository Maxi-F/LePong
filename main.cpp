#include "raylib.h"

struct Ball {
    Vector2 position;
    Vector2 velocity;
    int radius;

    void refreshVelocity() {
        if (position.x >= (GetScreenWidth() - radius) || (position.x <= radius)) velocity.x *= -1.0f;
        if (position.y >= (GetScreenHeight() - radius) || (position.y <= radius)) velocity.y *= -1.0f;
    }

    void refreshPosition() {
        position = { position.x + velocity.x, position.y + velocity.y };
    }
};

struct Paddle {
    Vector2 position;
    Vector2 size;
    KeyboardKey keyUp;
    KeyboardKey keyDown;
    int velocity;

    void checkInput() {
        if (IsKeyDown(keyUp) && position.y >= 0) position.y -= velocity;
        if (IsKeyDown(keyDown) && position.y <= (GetScreenHeight() - size.y)) position.y += velocity;
    }
};

const int BALL_RADIUS = 5;
const Vector2 BALL_VELOCITY = { 3.0f, 3.0f };
const Vector2 PADDLE_SIZE = { 5.0f, 40.0f };
const float PADDLE_MARGIN = 40.0f;
const int PADDLE_VELOCITY = 2.5f;

int getHalfScreen(int screenSize) {
    return screenSize / 2.0f;
}

int main()
{
    Vector2 ScreenDimensions = { 640, 480 };

    // Inicialización
    InitWindow(ScreenDimensions.x, ScreenDimensions.y, "LePong");

    int halfScreenWidth = getHalfScreen(GetScreenWidth());
    int halfScreenHeight = getHalfScreen(GetScreenHeight());

    Ball ball = {
        { halfScreenWidth, halfScreenHeight},
        BALL_VELOCITY,
        BALL_RADIUS
    };

    Paddle player1 = {
        { PADDLE_MARGIN, halfScreenHeight},
        PADDLE_SIZE,
        KEY_W,
        KEY_S,
        PADDLE_VELOCITY,
    };

    Paddle player2 = {
        { GetScreenWidth() - PADDLE_MARGIN, halfScreenHeight },
        PADDLE_SIZE,
        KEY_UP,
        KEY_DOWN,
        PADDLE_VELOCITY,
    };

    SetTargetFPS(60);

    // Loop
    while (!WindowShouldClose())
    {
        // Chequeo de Input

        player1.checkInput();
        player2.checkInput();

        // Actualización

        ball.refreshPosition();
        ball.refreshVelocity();

        // Dibujado
        BeginDrawing();
        ClearBackground(BLACK); // system("cls");

        DrawCircleV(ball.position, ball.radius, WHITE);
        DrawRectangleV(player1.position, player1.size, WHITE);
        DrawRectangleV(player2.position, player2.size, WHITE);

        EndDrawing();
    }

    // Cierre
    CloseWindow();
}
