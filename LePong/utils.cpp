#include "raylib.h"
#include "raymath.h"

float getHalf(int size) {
    return size / 2.0f;
}

int getDistanceFromMiddle(Rectangle rectangle, Vector2 point) {
    Vector2 middle = { rectangle.x + rectangle.width, rectangle.y + (rectangle.height / 2) };

    return point.y > middle.y ? Vector2Distance(middle, point) : -Vector2Distance(middle, point);
}
