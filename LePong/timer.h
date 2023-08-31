#pragma once

struct Timer {
	double startTime;
	double lifeTime;
	double pauseTime;
	bool paused;
};

void StartTimer(Timer* timer, double lifeTime);
bool TimerDone(Timer timer);
double GetElapsed(Timer timer);
void PauseTimer(Timer* timer);
void UnPauseTimer(Timer* timer);
