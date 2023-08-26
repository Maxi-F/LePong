#include "utils.h";
#include "constants.h";
#include "gameplay.h";
#include <string>;

void checkGameplayInputs(GameEntities* gameEntities) {
    for (int i = 0; i < 2; i++) {
        checkInput(gameEntities->players[i]);
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
            PADDLE_VELOCITY,
        },
        KEY_W,
        KEY_S,
        0
    };

    Player player2 = {
        {
            { GetScreenWidth() - PADDLE_MARGIN, halfScreenHeight - getHalf(PADDLE_SIZE.y), PADDLE_SIZE.x, PADDLE_SIZE.y },
            PADDLE_VELOCITY,
        },
        KEY_UP,
        KEY_DOWN,
        0
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

static void drawField() {
    const float MID_FIELD_LINE_WIDTH = 5.0f;
    const float MID_FIELD_CIRCLE_DIAMETER = 54.0f;
    const float MID_FIELD_CIRCLE_STROKE_WIDTH = 4.0f;
    const Rectangle MID_FIELD_LINE = { getHalf(GetScreenWidth()) - getHalf(MID_FIELD_LINE_WIDTH), 0, MID_FIELD_LINE_WIDTH, GetScreenHeight() };
    const Color FIELD_LINE_COLOR = { 143, 143, 143, 100 };

    DrawRectangleRec(MID_FIELD_LINE, FIELD_LINE_COLOR);
    DrawCircle(getHalf(GetScreenWidth()), getHalf(GetScreenHeight()), MID_FIELD_CIRCLE_DIAMETER, BLACK);
    DrawCircle(getHalf(GetScreenWidth()), getHalf(GetScreenHeight()), MID_FIELD_CIRCLE_DIAMETER, FIELD_LINE_COLOR);
    DrawCircle(getHalf(GetScreenWidth()), getHalf(GetScreenHeight()), MID_FIELD_CIRCLE_DIAMETER - MID_FIELD_CIRCLE_STROKE_WIDTH, BLACK);
    DrawCircle(getHalf(GetScreenWidth()), getHalf(GetScreenHeight()), MID_FIELD_LINE_WIDTH, FIELD_LINE_COLOR);
}

static void drawGameplayUI(GameEntities gameEntities) {
    GetFontDefault();
    const int SCORE_TEXT_FONT_SIZE = 50;
    const int SCORE_TEXT_MARGIN = 20;
    const float QUARTER_SCREEN_WIDTH = GetScreenWidth() / 4.0f;
    const float THREE_QUARTERS_SCREEN_WIDTH = 3.0f * QUARTER_SCREEN_WIDTH;

    DrawText(std::to_string(gameEntities.players[0].score).c_str(), QUARTER_SCREEN_WIDTH, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
    DrawText(std::to_string(gameEntities.players[1].score).c_str(), THREE_QUARTERS_SCREEN_WIDTH, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
}

void drawGameplay(GameEntities gameEntities) {
    ClearBackground(BLACK);
    drawField();
    drawGameplayUI(gameEntities);

    drawBall(gameEntities.ball);
    drawPaddle(gameEntities.players[0].paddle);
    drawPaddle(gameEntities.players[1].paddle);
}
