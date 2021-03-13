#include "stdafx.h"
#include "Timer.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

Timer::Timer()
	:currTime(0), fpsFrameCount(0), fpsTimeElapsed(0), frameRate(0),
	timeElapsed(0), worldTime(0)
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&preriodTime)) {
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		timeScale = 1.0f / preriodTime;
	}
	else {
		isHardware = false;
		lastTime = timeGetTime();
		timeScale = 0.001f;
	}
}

void Timer::UpdateTime(float frameLock)
{
	if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	else currTime = timeGetTime();

	timeElapsed = (currTime - lastTime) * timeScale;

	if (frameLock > 0.0f) {
		while (timeElapsed < (1.0f / frameLock)) {
			if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
			else currTime = timeGetTime();

			timeElapsed = (currTime - lastTime) * timeScale;
		}
	}

	lastTime = currTime;
	fpsFrameCount++;
	fpsTimeElapsed += timeElapsed;
	worldTime += timeElapsed;

	if (fpsTimeElapsed > 1.0f) {
		frameRate = fpsFrameCount;
		fpsFrameCount = 0;
		fpsTimeElapsed = 0.0f;
	}
}
