#include "raylib.h"
#include "timer.h"

void StartTimer(Timer* timer, double lifetime)
{
    timer->startTime = GetTime();
    timer->lifeTime = lifetime;
    timer->pauseTime = 0;
    timer->paused = false;
}

bool TimerDone(Timer timer)
{
    return !timer.paused && GetTime() - timer.startTime >= timer.lifeTime;
}

void PauseTimer(Timer* timer) {
    timer->pauseTime = GetTime();
    timer->paused = true;
}

void UnPauseTimer(Timer* timer) {
    timer->startTime += GetTime() - timer->pauseTime;
    timer->paused = false;
}

double GetElapsed(Timer timer)
{
    return GetTime() - timer.startTime;
}
