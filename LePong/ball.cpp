#include "raylib.h"
#include "paddle.h"
#include "ball.h"
#include "utils.h"
#include "constants.h"

extern const float BALL_RADIUS = 5.0f;
extern const float BALL_VELOCITY = 500.0f;
extern const float BALL_ACCELERATION = 1.05f;
extern const float MAX_BALL_ACCELERATION = 2000.0f;

static Rectangle getCollisionBox(Ball ball) {
    return { ball.position.x - ball.radius, ball.position.y - ball.radius, ball.radius * 2, ball.radius * 2 };
}

static float getDistancePercentageFromPaddle(Paddle paddle, Ball& ball) {
    float distance = getDistanceFromMiddle(paddle.rectangle, { ball.position.x + ball.radius, ball.position.y });
    float halfHeight = getHalf(paddle.rectangle.height);

    return clamp(1 - (halfHeight - distance) / halfHeight, -1, 1) * 0.5;
}

static float getValuePerBallDirection(Ball ball, float directionPositiveValue, float directionNegativeValue) {
    return ball.direction.x > 0 ? directionPositiveValue : directionNegativeValue;
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

void checkCollissionWith(Paddle paddle, Ball& ball) {
    if (checkRectangleCollision(paddle.rectangle, getCollisionBox(ball))) {
        float directionPercentage = getDistancePercentageFromPaddle(paddle, ball);

        ball.velocity = clamp(ball.velocity * BALL_ACCELERATION, BALL_VELOCITY, MAX_BALL_ACCELERATION);

        ball.direction = { getValuePerBallDirection(ball, moduleOf(directionPercentage) - 1, 1 - moduleOf(directionPercentage)), directionPercentage };

        float leftPaddleKnockback = paddle.rectangle.x + paddle.rectangle.width + ball.radius + 1.0f;
        float rightPaddleKnockback = paddle.rectangle.x - ball.radius - getWithFrameTime(1.0f);
        ball.position.x = getValuePerBallDirection(ball, leftPaddleKnockback, rightPaddleKnockback);
    }
}

void refreshVelocity(Ball& ball) {
    bool ballOnTopCollision = ball.position.y >= (GetScreenHeight() - ball.radius);
    bool ballOnBottomCollision = (ball.position.y <= ball.radius);
    
    if (ballOnTopCollision || ballOnBottomCollision) {
        if (ballOnTopCollision) {
            ball.position.y = GetScreenHeight() - ball.radius - 1.0f;
        }
        else {
            ball.position.y = ball.radius + 1.0f;
        }
        ball.direction.y *= -1.0f;
    };
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

void drawBall(Ball ball) {
    DrawCircleV(ball.position, ball.radius, WHITE);
}
