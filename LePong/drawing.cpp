#include "raylib.h"
#include "drawing.h"
#include "utils.h"
#include <string>

static void drawUI(GameEntities gameEntities) {
    GetFontDefault();
    const int SCORE_TEXT_FONT_SIZE = 50;
    const int SCORE_TEXT_MARGIN = 20;
    const float MID_FIELD_LINE_WIDTH = 5.0f;
    const Rectangle MID_FIELD_LINE = { getHalf(GetScreenWidth()) - getHalf(MID_FIELD_LINE_WIDTH), 0, MID_FIELD_LINE_WIDTH, GetScreenHeight() };

    DrawRectangleRec(MID_FIELD_LINE, { 143, 143, 143, 100 });

    DrawText(std::to_string(gameEntities.players[0].score).c_str(), GetScreenWidth() / 4.0f, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
    DrawText(std::to_string(gameEntities.players[1].score).c_str(), 3.0f * GetScreenWidth() / 4.0f, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, WHITE);
}

static void drawMenu() {

}

static void drawGameplay(GameEntities gameEntities) {
    ClearBackground(BLACK);
    drawUI(gameEntities);

    DrawCircleV(gameEntities.ball.position, gameEntities.ball.radius, WHITE);
    DrawRectangleRec(gameEntities.players[0].paddle.rectangle, PINK);
    DrawRectangleRec(gameEntities.players[1].paddle.rectangle, PINK);
}

void draw(Screens& screen, GameEntities gameEntities) {
    BeginDrawing();
    switch (screen) {
    case Screens::GAMEPLAY:
        drawGameplay(gameEntities);
        break;
    case Screens::MENU:
        drawMenu();
        break;
    }
    EndDrawing();
}
