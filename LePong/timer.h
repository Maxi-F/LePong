#pragma once

struct Timer {
	double startTime;
	double lifeTime;
};

void StartTimer(Timer* timer, double lifeTime);
bool TimerDone(Timer timer);
double GetElapsed(Timer timer);
