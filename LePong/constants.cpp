#include "raylib.h"
#include "utils.h"

extern const float BALL_RADIUS = 5.0f;
extern const Vector2 BALL_VELOCITY = { 250.0f, 250.0f };
extern const float BALL_ACCELERATION = 1.05f;
extern const float MAX_BALL_ACCELERATION = 1000.0f;
extern const Vector2 PADDLE_SIZE = { 5.0f, 120.0f };
extern const float PADDLE_MARGIN = 40.0f;
extern const float PADDLE_VELOCITY = 400.0f;
extern const int MAX_SCORE = 5;
