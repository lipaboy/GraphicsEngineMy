#include "Time.h"
#include <time.h>
#include <chrono>

namespace graphics_engine {

bool Time::isInited = false;

Time::Type Time::startClock = //Time::ClockType::now();
        0.0;

double Time::curFrameTime = 0.0;
double Time::prevFrameTime = 0.0;

double Time::time = 0.0;
double Time::deltaTime = 0.0;

int Time::frameCount = 0;

void Time::Update()
{
	if (false == isInited)
	{
//		startClock	= clock();
        startClock = //Time::ClockType::now();
                0.0;
		isInited	= true;
	}

    curFrameTime = (clock() - startClock) / CLOCKS_PER_SEC;
//    curFrameTime = duration_cast<nanoseconds>(Time::ClockType::now() - startClock).count() / 1e9;

	time		= curFrameTime;
	deltaTime	= curFrameTime - prevFrameTime;

	prevFrameTime = curFrameTime;

	++frameCount;
}

}
