#include "raylib.h"
#include <iostream>
#include "raymath.h"

const int BALL_RADIUS = 5;
const Vector2 BALL_VELOCITY = { 3.0f, 3.0f };
const float BALL_ACCELERATION = 1.2f;
const float MAX_BALL_ACCELERATION = 15.0f;
const Vector2 PADDLE_SIZE = { 5.0f, 120.0f };
const float PADDLE_MARGIN = 40.0f;
const int PADDLE_VELOCITY = 4.0f;

int getHalf(int size) {
    return size / 2.0f;
}

struct Paddle {
    Rectangle rectangle;
    KeyboardKey keyUp;
    KeyboardKey keyDown;
    int velocity;

    void checkInput() {
        if (IsKeyDown(keyUp) && rectangle.y >= 0) rectangle.y -= velocity;
        if (IsKeyDown(keyDown) && rectangle.y <= GetScreenHeight() - rectangle.height) rectangle.y += velocity;
    }
};

int getDistanceFromMiddle(Rectangle rectangle, Vector2 point) {
    Vector2 middle = { rectangle.x + rectangle.width, rectangle.y + (rectangle.height / 2) };

    return point.y > middle.y ? Vector2Distance(middle, point) : -Vector2Distance(middle, point);
}

struct Ball {
    Vector2 position;
    Vector2 velocity;
    int radius;

    void checkCollissionWith(Paddle paddle) {
        if (CheckCollisionCircleRec(position, radius, paddle.rectangle)) {
            float distance = getDistanceFromMiddle(paddle.rectangle, { position.x + radius, position.y });
            float halfHeight = getHalf(paddle.rectangle.height);

            float percentage = 1 - (halfHeight - distance) / halfHeight;

            velocity.x *= -BALL_ACCELERATION;
            velocity.x = velocity.x > 0 ? Clamp(velocity.x, BALL_VELOCITY.x, MAX_BALL_ACCELERATION) : Clamp(velocity.x, -MAX_BALL_ACCELERATION, -BALL_VELOCITY.x);
            velocity.y = BALL_VELOCITY.y * percentage;
        }
    }

    void refreshVelocity() {
        if (position.y >= (GetScreenHeight() - radius) || (position.y <= radius)) velocity.y *= -1.0f;
    }

    void refreshPosition(Vector2 initialPosition) {
        position = { position.x + velocity.x, position.y + velocity.y };
        if (position.x >= (GetScreenWidth() - radius) || (position.x <= radius)) { 
            position = initialPosition;
            velocity.x = velocity.x > 0 ? BALL_VELOCITY.x : -BALL_VELOCITY.x;
        };
    }
};

int main()
{
    Vector2 ScreenDimensions = { 640, 480 };

    // Inicialización
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

    SetTargetFPS(60);

    // Loop
    while (!WindowShouldClose())
    {
        // Chequeo de Input

        player1.checkInput();
        player2.checkInput();

        // Actualización

        ball.checkCollissionWith(player1);
        ball.checkCollissionWith(player2);
        ball.refreshPosition(initialBallPosition);
        ball.refreshVelocity();

        // Dibujado
        BeginDrawing();
        ClearBackground(BLACK); // system("cls");

        DrawCircleV(ball.position, ball.radius, WHITE);
        DrawRectangleRec(player1.rectangle, PINK);
        DrawRectangleRec(player2.rectangle, PINK);

        EndDrawing();
    }

    // Cierre
    CloseWindow();
}
