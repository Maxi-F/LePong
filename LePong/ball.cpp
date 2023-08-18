#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "utils.h"
#include "constants.h"
#include "raymath.h"

void checkCollissionWith(Paddle paddle, Ball& ball) {
    if (CheckCollisionCircleRec(ball.position, ball.radius, paddle.rectangle)) {
        float distance = getDistanceFromMiddle(paddle.rectangle, { ball.position.x + ball.radius, ball.position.y });
        float halfHeight = getHalf(paddle.rectangle.height);

        float percentage = 1 - (halfHeight - distance) / halfHeight;

        ball.velocity.x *= -BALL_ACCELERATION;
        ball.velocity.x = ball.velocity.x > 0 ? Clamp(ball.velocity.x, BALL_VELOCITY.x, MAX_BALL_ACCELERATION) : Clamp(ball.velocity.x, -MAX_BALL_ACCELERATION, -BALL_VELOCITY.x);
        ball.velocity.y = BALL_VELOCITY.y * percentage;
    }
}

void refreshVelocity(Ball& ball) {
    if (ball.position.y >= (GetScreenHeight() - ball.radius) || (ball.position.y <= ball.radius)) ball.velocity.y *= -1.0f;
}

void refreshPosition(Ball& ball) {
    ball.position = { ball.position.x + ball.velocity.x, ball.position.y + ball.velocity.y };
    if (ball.position.x >= (GetScreenWidth() - ball.radius) || (ball.position.x <= ball.radius)) {
        ball.position = { getHalf(GetScreenWidth()), getHalf(GetScreenHeight()) };
        ball.velocity.x = ball.velocity.x > 0 ? BALL_VELOCITY.x : -BALL_VELOCITY.x;
    };
}
