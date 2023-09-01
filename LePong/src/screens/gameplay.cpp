#include "../utils.h";
#include "../constants.h";
#include "gameplay.h";
#include <string>;
#include <iostream>;

GameplayEntities initGameplay(bool isAgainstCpu) {
    int halfScreenWidth = getHalf(GetScreenWidth());
    int halfScreenHeight = getHalf(GetScreenHeight());

    Vector2 initialBallPosition = { halfScreenWidth, halfScreenHeight };

    Ball ball = {
        initialBallPosition,
        { getHalf(getRandomNegativeOrPositive()), getHalf(getRandomNegativeOrPositive()) },
        BALL_VELOCITY,
        BALL_RADIUS,
        1
    };

    Paddle player1Paddle = {
        { PADDLE_MARGIN, halfScreenHeight - getHalf(PADDLE_SIZE.y), PADDLE_SIZE.x, PADDLE_SIZE.y },
        PADDLE_VELOCITY,
    };

    Player player1 = {
        player1Paddle,
        KEY_W,
        KEY_S,
        "Player 1",
        false,
        0
    };

    Paddle player2Paddle = {
        { GetScreenWidth() - PADDLE_MARGIN - PADDLE_SIZE.x, halfScreenHeight - getHalf(PADDLE_SIZE.y), PADDLE_SIZE.x, PADDLE_SIZE.y },
        PADDLE_VELOCITY,
    };

    Player player2 = {
        player2Paddle,
        KEY_UP,
        KEY_DOWN,
        isAgainstCpu ? "CPU" : "Player 2",
        isAgainstCpu,
        0
    };

    Timer timer;

    StartTimer(&timer, GetRandomValue(5, 10));

    return { {player1, player2}, ball, { PowerUpType::EMPTY }, timer };
}

static void modifyScore(GameplayEntities* gameEntities) {
    if (isBallOnLeftEdge(gameEntities->ball) || isBallOnRightEdge(gameEntities->ball)) {
        if (isBallOnLeftEdge(gameEntities->ball)) {
            gameEntities->players[1].score += gameEntities->ball.points;
        }
        else {
            gameEntities->players[0].score += gameEntities->ball.points;
        }
        gameEntities->ball.points = 1;
        gameEntities->powerUp = { PowerUpType::EMPTY };
        StartTimer(&gameEntities->timerForPowerUp, GetRandomValue(5, 10));

        for (int i = 0; i < 2; i++) {
            resetPaddle(gameEntities->players[i].paddle);
        }
    }
}

static bool anyPlayerHasWon(GameplayEntities* gameEntities) {
    return playerHasWon(gameEntities->players[0]) || playerHasWon(gameEntities->players[1]);
}

void checkGameplayInputs(GameplayEntities* gameEntities, Screens &screen, bool& shouldClose) {
    if (WindowShouldClose()) {
        shouldClose = true;
        return;
    }

    if (!anyPlayerHasWon(gameEntities)) {
        if (gameEntities->isPaused) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                gameEntities->isPaused = false;
                UnPauseTimer(&gameEntities->timerForPowerUp);
            }
            else if (IsKeyPressed(KEY_ENTER)) {
                screen = Screens::MENU;
            }
            return;
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            gameEntities->isPaused = true;
            PauseTimer(&gameEntities->timerForPowerUp);
            return;
        }

        for (int i = 0; i < 2; i++) {
            checkInput(gameEntities->players[i]);
        }

    }
    else {
        if (IsKeyPressed(KEY_ENTER)) {
            screen = Screens::MENU;
        }
    }
}

void updateCpuMovement(GameplayEntities* gameplayEntities) {
    if (!anyPlayerHasWon(gameplayEntities) && !gameplayEntities->isPaused) {
        for (int i = 0; i < 2; i++) {
            updateCpuPlayerMovement(gameplayEntities->players[i], gameplayEntities->ball);
        }
    }
}

void updatePowerUp(GameplayEntities& gameEntities) {
    if (TimerDone(gameEntities.timerForPowerUp)) {
        generateRandomPowerUp(gameEntities.powerUp);
        StartTimer(&gameEntities.timerForPowerUp, GetRandomValue(10, 15));
    }
    else if (checkBallCollisionWith(gameEntities.powerUp.rectangle, gameEntities.ball) && !gameEntities.isPaused) {
        int player = gameEntities.ball.direction.x > 0 ? 0 : 1;
        checkPowerUpCollision(gameEntities.powerUp, gameEntities.ball, gameEntities.players[player].paddle);
        gameEntities.powerUp = { PowerUpType::EMPTY };
        StartTimer(&gameEntities.timerForPowerUp, GetRandomValue(10, 15));
    }
};

void checkGameplayCollisions(GameplayEntities* gameEntities) {
    if (!anyPlayerHasWon(gameEntities) && !gameEntities->isPaused) {
        checkCollissionWith(gameEntities->players[0].paddle, gameEntities->ball);
        checkCollissionWith(gameEntities->players[1].paddle, gameEntities->ball);

        refreshPosition(gameEntities->ball);
        modifyScore(gameEntities);

        refreshToInitialPosition(gameEntities->ball);

        refreshVelocity(gameEntities->ball);
    }

}

static void drawField() {
    const float HALF_SCREEN_WIDTH = getHalf(GetScreenWidth());
    const float HALF_SCREEN_HEIGHT = getHalf(GetScreenHeight());

    const float MID_FIELD_LINE_WIDTH = 5.0f;
    const float MID_FIELD_CIRCLE_DIAMETER = 54.0f;
    const float MID_FIELD_CIRCLE_STROKE_WIDTH = 4.0f;
    const Rectangle MID_FIELD_LINE = { HALF_SCREEN_WIDTH - getHalf(MID_FIELD_LINE_WIDTH), 0, MID_FIELD_LINE_WIDTH, GetScreenHeight() };
    const Color FIELD_LINE_COLOR = { 143, 143, 143, 100 };

    DrawRectangleRec(MID_FIELD_LINE, FIELD_LINE_COLOR);
    DrawCircle(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, MID_FIELD_CIRCLE_DIAMETER, BLACK);
    DrawCircle(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, MID_FIELD_CIRCLE_DIAMETER, FIELD_LINE_COLOR);
    DrawCircle(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, MID_FIELD_CIRCLE_DIAMETER - MID_FIELD_CIRCLE_STROKE_WIDTH, BLACK);
    DrawCircle(HALF_SCREEN_WIDTH, HALF_SCREEN_HEIGHT, MID_FIELD_LINE_WIDTH, FIELD_LINE_COLOR);
}

static void drawGameplayUI(GameplayEntities gameEntities) {
    const int SCORE_TEXT_FONT_SIZE = 50;
    const int SCORE_TEXT_MARGIN = 20;
    const float QUARTER_SCREEN_WIDTH = GetScreenWidth() / 4.0f;
    const float THREE_QUARTERS_SCREEN_WIDTH = 3.0f * QUARTER_SCREEN_WIDTH;

    DrawText(std::to_string(gameEntities.players[0].score).c_str(), QUARTER_SCREEN_WIDTH, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
    DrawText(std::to_string(gameEntities.players[1].score).c_str(), THREE_QUARTERS_SCREEN_WIDTH, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
}

static void drawCenterBox(const char* upperText, const char* bottomText) {
    const float RECTANGLE_WIDTH = 300.0f;
    const float RECTANGLE_HEIGHT = 120.0f;
    const float RECTANGLE_BORDER_STROKE = 5.0f;
    const float RECTANGLE_X_POSITION = getHalf(GetScreenWidth()) - getHalf(RECTANGLE_WIDTH);
    const float RECTANGLE_Y_POSITION = getHalf(GetScreenHeight()) - getHalf(RECTANGLE_HEIGHT);
    const Color RECTANGLE_COLOR = { 96, 96, 255, 255 };
    const Color RECTANGLE_BORDER_COLOR = { 52, 52, 125, 255 };

    const float TEXT_PADDING = 20.0f;
    const float WIN_TEXT_FONT_SIZE = 20.0f;
    const float GO_BACK_FONT_SIZE = 16.0f;
   
    Rectangle rectangle = {
        RECTANGLE_X_POSITION,
        RECTANGLE_Y_POSITION,
        RECTANGLE_WIDTH,
        RECTANGLE_HEIGHT
    };

    Rectangle insideRectangle = {
        RECTANGLE_X_POSITION + RECTANGLE_BORDER_STROKE,
        RECTANGLE_Y_POSITION + RECTANGLE_BORDER_STROKE,
        RECTANGLE_WIDTH - RECTANGLE_BORDER_STROKE * 2,
        RECTANGLE_HEIGHT - RECTANGLE_BORDER_STROKE * 2
    };

    DrawRectangleRec(rectangle, RECTANGLE_BORDER_COLOR);
    DrawRectangleRec(insideRectangle, RECTANGLE_COLOR);

    DrawText(
        upperText,
        RECTANGLE_X_POSITION + TEXT_PADDING,
        RECTANGLE_Y_POSITION + TEXT_PADDING,
        WIN_TEXT_FONT_SIZE,
        BLACK
    );

    Vector2 bottomTextMeasures = MeasureTextEx(GetFontDefault(), bottomText, GO_BACK_FONT_SIZE, (3 * GO_BACK_FONT_SIZE) / 2);

    DrawText(
        bottomText,
        RECTANGLE_X_POSITION + TEXT_PADDING,
        RECTANGLE_Y_POSITION + insideRectangle.height - roundUp(bottomTextMeasures.y, TEXT_PADDING),
        GO_BACK_FONT_SIZE,
        BLACK
    );
}

static void drawWinBox(Player player) {
    std::string winText = player.name.append(" has won!");
    const char* PRESS_ENTER_FOR_MENU_TEXT = "Press 'enter' to go back to menu";

    drawCenterBox(winText.c_str(), PRESS_ENTER_FOR_MENU_TEXT);
}

static void drawPauseBox() {
    drawCenterBox("Paused", "Press ESC to unpause\nENTER for Menu");
}

void drawGameplay(GameplayEntities gameEntities) {
    drawField();
    
    if (!isNotSetted(gameEntities.powerUp)) {
        drawPowerUp(gameEntities.powerUp);
    }

    drawGameplayUI(gameEntities);

    drawBall(gameEntities.ball);
    drawPaddle(gameEntities.players[0].paddle);
    drawPaddle(gameEntities.players[1].paddle);

    if (playerHasWon(gameEntities.players[0])) {
        drawWinBox(gameEntities.players[0]);
    }

    if (gameEntities.isPaused) {
        drawPauseBox();
    }

    else if (playerHasWon(gameEntities.players[1])) {
        drawWinBox(gameEntities.players[1]);
    }
}