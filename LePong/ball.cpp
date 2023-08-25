#include <iostream>
#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "utils.h"
#include "constants.h"
using namespace std;

static Rectangle getCollisionBox(Ball ball) {
    return { ball.position.x - ball.radius, ball.position.y - ball.radius, ball.radius * 2, ball.radius * 2 };
}

void refreshToInitialPosition(Ball& ball) {
    ball.position = { getHalf(GetScreenWidth()), getHalf(GetScreenHeight()) + GetRandomValue(-200, 200) };
    ball.velocity = { ball.velocity.x > 0 ? BALL_VELOCITY.x : -BALL_VELOCITY.x, getRandomNegativeOrPositive() * BALL_VELOCITY.y };
}

void checkCollissionWith(Paddle paddle, Ball& ball) {
    if (checkRectangleCollision(paddle.rectangle, getCollisionBox(ball))) {
        float distance = getDistanceFromMiddle(paddle.rectangle, { ball.position.x + ball.radius, ball.position.y });
        float halfHeight = getHalf(paddle.rectangle.height);

        float percentage = clamp(1 - (halfHeight - distance) / halfHeight, -1, 1);

        cout << "BEFORE: " << "X=" << ball.velocity.x << ", Y=" << ball.velocity.y << ", PERCENTAGE= " << percentage << endl;

        ball.velocity.x *= -BALL_ACCELERATION;
        ball.velocity.x = ball.velocity.x > 0 ? clamp(ball.velocity.x, BALL_VELOCITY.x, MAX_BALL_ACCELERATION) : clamp(ball.velocity.x, -MAX_BALL_ACCELERATION, -BALL_VELOCITY.x);
        ball.velocity.y = moduleOf(ball.velocity.x) * percentage;

        cout << "AFTER: " << "X=" << ball.velocity.x << ", Y=" << ball.velocity.y << endl;

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

void refreshPosition(Ball& ball) {
    ball.position = { ball.position.x + getWithFrameTime(ball.velocity.x), ball.position.y + getWithFrameTime(ball.velocity.y) };
    if (ball.position.x >= (GetScreenWidth() - ball.radius) || (ball.position.x <= ball.radius)) {
        refreshToInitialPosition(ball);
    };
}
