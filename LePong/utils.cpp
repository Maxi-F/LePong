#include "raylib.h"
#include "raymath.h"

float clamp(float value, float min, float max)
{
    return (value < min) ? min : value > max ? max : value;
}

bool checkRectangleCollision(Rectangle rectangle1, Rectangle rectangle2) {
    float rectangle1LeftEdge = rectangle1.x;
    float rectangle1RightEdge = rectangle1.x + rectangle1.width;
    
    float rectangle2LeftEdge = rectangle2.x;
    float rectangle2RightEdge = rectangle2.x + rectangle2.width;

    float rectangle1BottomEdge = rectangle1.y + rectangle1.height;
    float rectangle1TopEdge = rectangle1.y;
    
    float rectangle2BottomEdge = rectangle2.y + rectangle2.height;
    float rectangle2TopEdge = rectangle2.y;

    return rectangle1RightEdge >= rectangle2LeftEdge &&
        rectangle1LeftEdge <= rectangle2RightEdge &&
        rectangle1BottomEdge >= rectangle2TopEdge &&
        rectangle1TopEdge <= rectangle2BottomEdge;
};

float getHalf(int size) {
    return size / 2.0f;
}

float getWithFrameTime(float value) {
    return value * GetFrameTime();
}

float getDistanceFromMiddle(Rectangle rectangle, Vector2 point) {
    float middle = rectangle.y + (rectangle.height / 2);

    return point.y - middle;
}
