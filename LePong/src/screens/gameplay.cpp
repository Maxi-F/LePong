#include "../utils.h";
#include "../constants.h";
#include "draws/gameplayDraws.h";
#include <string>;

static Camera3D initCamera() {
    Camera3D camera = { 0 };
    camera.position = { 0.0f, SCREEN_DIMENSIONS.x, FIELD_DIMENSIONS.y };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 0.5f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

GameplayEntities initGameplay(bool isAgainstCpu) {
    int halfFieldWidth = getHalf(FIELD_DIMENSIONS.x);
    int halfFieldHeight = getHalf(FIELD_DIMENSIONS.y);

    Camera3D camera = initCamera();

    Ball ball = initBall();

    Paddle player1Paddle = initPaddle(-halfFieldWidth + PADDLE_MARGIN, SKYBLUE, DARKBLUE);

    Player player1 = {
        player1Paddle,
        KEY_W,
        KEY_S,
        "Player 1",
        false,
        0
    };

    Paddle player2Paddle = initPaddle(halfFieldWidth - PADDLE_MARGIN - PADDLE_SIZE.x, LIME, DARKGREEN);

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

    return { {player1, player2}, ball, { PowerUpType::EMPTY }, timer, { camera, CAMERA_FIRST_PERSON } };
}

static void modifyScore(GameplayEntities* gameEntities) {
    if (isBallOnLeftEdge(gameEntities->ball) || isBallOnRightEdge(gameEntities->ball)) {
        if (isBallOnLeftEdge(gameEntities->ball)) {
            addScore(gameEntities->players[1], gameEntities->ball.points);
        }
        else {
            addScore(gameEntities->players[0], gameEntities->ball.points);
        }

        gameEntities->ball.points = 1;
        gameEntities->powerUp = { PowerUpType::EMPTY };
        gameEntities->camera.cameraMode = CAMERA_FIRST_PERSON;
        StartTimer(&gameEntities->timerForPowerUp, GetRandomValue(5, 10));

        for (int i = 0; i < 2; i++) {
            resetPaddle(gameEntities->players[i].paddle);
        }
    }
}

static bool anyPlayerHasWon(GameplayEntities* gameEntities) {
    return playerHasWon(gameEntities->players[0]) || playerHasWon(gameEntities->players[1]);
}

void updateCamera(GameplayEntities& gameEntities) {
    if (gameEntities.camera.cameraMode == CAMERA_ORBITAL) {
        UpdateCamera(&gameEntities.camera.camera, gameEntities.camera.cameraMode);
    }
}

void checkGameplayInputs(GameplayEntities* gameEntities, Screens& screen, bool& shouldClose) {
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
        checkPowerUpCollision(gameEntities.powerUp, gameEntities.ball, gameEntities.players[player].paddle, gameEntities.camera.cameraMode);
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

void drawGameplay(GameplayEntities gameEntities) {
    ClearBackground(LIGHTGRAY);

    BeginMode3D(gameEntities.camera.camera);

        drawField();

        if (!isNotSetted(gameEntities.powerUp)) {
            drawPowerUp(gameEntities.powerUp);
        }

        drawBall(gameEntities.ball);
        drawPaddle(gameEntities.players[0].paddle);
        drawPaddle(gameEntities.players[1].paddle);

    EndMode3D();

    drawGameplayUI(gameEntities);

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
