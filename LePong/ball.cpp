#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "utils.h"
#include "constants.h"

static Rectangle getCollisionBox(Ball ball) {
    return { ball.position.x - ball.radius, ball.position.y - ball.radius, ball.radius * 2, ball.radius * 2 };
}

void checkCollissionWith(Paddle paddle, Ball& ball) {
    if (checkRectangleCollision(paddle.rectangle, getCollisionBox(ball))) {
        float distance = getDistanceFromMiddle(paddle.rectangle, { ball.position.x + ball.radius, ball.position.y });
        float halfHeight = getHalf(paddle.rectangle.height);

        float percentage = clamp(1 - (halfHeight - distance) / halfHeight, -1, 1);

        ball.velocity.x *= -BALL_ACCELERATION;
        ball.velocity.x = ball.velocity.x > 0 ? clamp(ball.velocity.x, BALL_VELOCITY.x, MAX_BALL_ACCELERATION) : clamp(ball.velocity.x, -MAX_BALL_ACCELERATION, -BALL_VELOCITY.x);
        ball.velocity.y = moduleOf(ball.velocity.x) * percentage;

        ball.position.x = ball.velocity.x > 0 ? paddle.rectangle.x + paddle.rectangle.width + ball.radius + getWithFrameTime(1.0f) : paddle.rectangle.x - ball.radius - getWithFrameTime(1.0f);
    }
}

void refreshVelocity(Ball& ball) {
    bool ballOnTopCollision = ball.position.y >= (GetScreenHeight() - ball.radius);
    bool ballOnBottomCollision = (ball.position.y <= ball.radius);
    
    if (ballOnTopCollision || ballOnBottomCollision) {
        if (ballOnTopCollision) {
            ball.position.y = GetScreenHeight() - ball.radius - getWithFrameTime(1.0f);
        }
        else {
            ball.position.y = ball.radius + getWithFrameTime(1.0f);
        }
        ball.velocity.y *= -1.0f;
    };
}

bool isBallOnLeftEdge(Ball& ball) {
    return ball.position.x <= ball.radius;
}

bool isBallOnRightEdge(Ball& ball) {
    return ball.position.x >= (GetScreenWidth() - ball.radius);
}

static bool isBallOnEdge(Ball& ball) {
    return isBallOnLeftEdge(ball) || isBallOnRightEdge(ball);
}

void refreshToInitialPosition(Ball& ball) {
    const int BALL_APARITION_RANGE = 200;
    if (isBallOnEdge(ball)) {
        ball.position = { getHalf(GetScreenWidth()), getHalf(GetScreenHeight()) + GetRandomValue(-BALL_APARITION_RANGE, BALL_APARITION_RANGE) };
        ball.velocity = { ball.velocity.x > 0 ? BALL_VELOCITY.x : -BALL_VELOCITY.x, getRandomNegativeOrPositive() * BALL_VELOCITY.y };
    };
}

void refreshPosition(Ball& ball) {
    ball.position = { ball.position.x + getWithFrameTime(ball.velocity.x), ball.position.y + getWithFrameTime(ball.velocity.y) };
}
