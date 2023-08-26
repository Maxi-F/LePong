#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "utils.h"
#include "constants.h"
#include <iostream>
using namespace std;

static Rectangle getCollisionBox(Ball ball) {
    return { ball.position.x - ball.radius, ball.position.y - ball.radius, ball.radius * 2, ball.radius * 2 };
}

void checkCollissionWith(Paddle paddle, Ball& ball) {
    if (checkRectangleCollision(paddle.rectangle, getCollisionBox(ball))) {
        float distance = getDistanceFromMiddle(paddle.rectangle, { ball.position.x + ball.radius, ball.position.y });
        float halfHeight = getHalf(paddle.rectangle.height);

        float percentage = clamp(1 - (halfHeight - distance) / halfHeight, -1, 1) * 0.5;

        cout << "PERCENTAGE: " << percentage << endl;

        ball.velocity *= BALL_ACCELERATION;
        ball.velocity = clamp(ball.velocity, BALL_VELOCITY, MAX_BALL_ACCELERATION);
        cout << "X: " << ball.direction.x << ", Y: " << ball.direction.y << endl;

        ball.direction = { ball.direction.x > 0 ? moduleOf(percentage) - 1 : 1 - moduleOf(percentage), percentage };

        cout << "AFTER: " << "X: " << ball.direction.x << ", Y: " << ball.direction.y << endl;

        ball.position.x = ball.direction.x > 0 ? paddle.rectangle.x + paddle.rectangle.width + ball.radius + getWithFrameTime(1.0f) : paddle.rectangle.x - ball.radius - getWithFrameTime(1.0f);
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
        ball.direction.y *= -1.0f;
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
        ball.direction = { getHalf(ball.direction.x > 0 ? 1 : -1), getHalf(getRandomNegativeOrPositive()) };
        ball.velocity = BALL_VELOCITY;
    };
}

void refreshPosition(Ball& ball) {
    ball.position = { ball.position.x + getWithFrameTime(ball.velocity * ball.direction.x), ball.position.y + getWithFrameTime(ball.velocity * ball.direction.y) };
}
