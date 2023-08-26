#include "utils.h";
#include "constants.h";
#include "gameplay.h";
#include <string>;

void checkGameplayInputs(GameEntities* gameEntities) {
    for (int i = 0; i < 2; i++) {
        checkInput(gameEntities->players[i].paddle);
    }
}

GameEntities initGameplay() {
    int halfScreenWidth = getHalf(GetScreenWidth());
    int halfScreenHeight = getHalf(GetScreenHeight());

    Vector2 initialBallPosition = { halfScreenWidth, halfScreenHeight };

    Ball ball = {
        initialBallPosition,
        { getHalf(getRandomNegativeOrPositive()), getHalf(getRandomNegativeOrPositive()) },
        BALL_VELOCITY,
        BALL_RADIUS
    };

    Player player1 = {
        {
            { PADDLE_MARGIN, halfScreenHeight - getHalf(PADDLE_SIZE.y), PADDLE_SIZE.x, PADDLE_SIZE.y },
            KEY_W,
            KEY_S,
            PADDLE_VELOCITY,
        },
        0
    };

    Player player2 = {
        {
            { GetScreenWidth() - PADDLE_MARGIN, halfScreenHeight - getHalf(PADDLE_SIZE.y), PADDLE_SIZE.x, PADDLE_SIZE.y },
            KEY_UP,
            KEY_DOWN,
            PADDLE_VELOCITY,
        }
    };

    return { {player1, player2}, ball };
}

static void modifyScore(GameEntities* gameEntities) {
    if (isBallOnLeftEdge(gameEntities->ball)) {
        gameEntities->players[1].score++;
    }
    else if (isBallOnRightEdge(gameEntities->ball)) {
        gameEntities->players[0].score++;
    }
}

void checkGameplayCollisions(GameEntities* gameEntities) {
    checkCollissionWith(gameEntities->players[0].paddle, gameEntities->ball);
    checkCollissionWith(gameEntities->players[1].paddle, gameEntities->ball);

    refreshPosition(gameEntities->ball);
    modifyScore(gameEntities);

    refreshToInitialPosition(gameEntities->ball);

    refreshVelocity(gameEntities->ball);
}

static void drawGameplayUI(GameEntities gameEntities) {
    GetFontDefault();
    const int SCORE_TEXT_FONT_SIZE = 50;
    const int SCORE_TEXT_MARGIN = 20;
    const float MID_FIELD_LINE_WIDTH = 5.0f;
    const Rectangle MID_FIELD_LINE = { getHalf(GetScreenWidth()) - getHalf(MID_FIELD_LINE_WIDTH), 0, MID_FIELD_LINE_WIDTH, GetScreenHeight() };

    DrawRectangleRec(MID_FIELD_LINE, { 143, 143, 143, 100 });

    DrawText(std::to_string(gameEntities.players[0].score).c_str(), GetScreenWidth() / 4.0f, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
    DrawText(std::to_string(gameEntities.players[1].score).c_str(), 3.0f * GetScreenWidth() / 4.0f, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
}

void drawGameplay(GameEntities gameEntities) {
    ClearBackground(BLACK);
    drawGameplayUI(gameEntities);

    DrawCircleV(gameEntities.ball.position, gameEntities.ball.radius, WHITE);
    DrawRectangleRec(gameEntities.players[0].paddle.rectangle, PINK);
    DrawRectangleRec(gameEntities.players[1].paddle.rectangle, PINK);
}
