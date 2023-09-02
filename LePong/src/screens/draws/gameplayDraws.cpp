#include "../../constants.h"
#include "../../utils.h"
#include "raylib.h"
#include "gameplayDraws.h"
#include <string>

void drawField() {
    const float HALF_FIELD_WIDTH = getHalf(FIELD_DIMENSIONS.x);
    const float HALF_FIELD_HEIGHT = getHalf(FIELD_DIMENSIONS.y);

    const float MID_FIELD_LINE_WIDTH = 5.0f;
    const float MID_FIELD_CIRCLE_RADIUS = 28.0f;
    const float MID_FIELD_CIRCLE_STROKE_WIDTH = 4.0f;
    const Color FIELD_LINE_COLOR = { 143, 143, 143, 100 };
    const Vector3 CENTER = { 0.0f, 0.0f, 0.0f };

    DrawPlane(CENTER, { FIELD_DIMENSIONS.x, FIELD_DIMENSIONS.y }, BLACK);

    DrawCubeV(CENTER, { MID_FIELD_LINE_WIDTH, 1.0f, FIELD_DIMENSIONS.y }, FIELD_LINE_COLOR);

    DrawCylinder(CENTER, MID_FIELD_CIRCLE_RADIUS, MID_FIELD_CIRCLE_RADIUS, 5.0, MID_FIELD_CIRCLE_RADIUS, BLACK);
    DrawCylinder(CENTER, MID_FIELD_CIRCLE_RADIUS, MID_FIELD_CIRCLE_RADIUS, 5.0, MID_FIELD_CIRCLE_RADIUS, FIELD_LINE_COLOR);
}

void drawGameplayUI(GameplayEntities gameEntities) {
    const int SCORE_TEXT_FONT_SIZE = 50;
    const int SCORE_TEXT_MARGIN = 20;
    const float QUARTER_SCREEN_WIDTH = GetScreenWidth() / 4.0f;
    const float THREE_QUARTERS_SCREEN_WIDTH = 3.0f * QUARTER_SCREEN_WIDTH;

    DrawText(std::to_string(gameEntities.players[0].score).c_str(), QUARTER_SCREEN_WIDTH, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, BLACK);
    DrawText(std::to_string(gameEntities.players[1].score).c_str(), THREE_QUARTERS_SCREEN_WIDTH, SCORE_TEXT_MARGIN, SCORE_TEXT_FONT_SIZE, BLACK);
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

void drawWinBox(Player player) {
    std::string winText = player.name.append(" has won!");
    const char* PRESS_ENTER_FOR_MENU_TEXT = "Press 'enter' to go back to menu";

    drawCenterBox(winText.c_str(), PRESS_ENTER_FOR_MENU_TEXT);
}

void drawPauseBox() {
    drawCenterBox("Paused", "Press ESC to unpause\nENTER for Menu");
}
