#pragma once

#include <chrono>

namespace graphics_engine {

using std::chrono::steady_clock;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::nanoseconds;

class Time
{
public:
    using ClockType = high_resolution_clock;
    using Type = //ClockType::time_point;
        double;

public:

	static void Update();

	/*
	* @brief The time in seconds since the run of the application.
	*/
	static double GetTime()
	{
		return time;
	}

	/*
	* @brief The time in seconds have been needed to render the last frame.
	*/
	static double GetDeltaTime()
	{
		return deltaTime;
	}

	/*
	* @brief The number of frames that have been rendered.
	*/
	static double GetFrameCount()
	{
		return frameCount;
	}

private:

	static bool isInited;

    static Type startClock;

	static double curFrameTime;
	static double prevFrameTime;

	static double time;
	static double deltaTime;

	static int frameCount;
};

}
