// FreezeTime
// Andre Berthiaume, Jan 2016

#ifndef _FreezeTime 
#define _FreezeTime

#include "Keyboard.h"
#include <chrono>

class FreezeTime
{
private:
	static const SURREAL_KEY FREEZE_KEY = SURREAL_KEY::F10_KEY;
	static const SURREAL_KEY SINGLE_FRAME_KEY = SURREAL_KEY::F9_KEY;

	static const float DEAD_TIME_THRESHOLD;
	static const float DEFAULT_FRAME_TIME;

	float totalFrozenTime;
	bool freeze_mode_active;

	using clock = std::chrono::high_resolution_clock;
	clock::time_point start_time;


	bool HackedKeyRelease(SURREAL_KEY k);
	void TestForFreezeKeys();

public:
	FreezeTime();
	~FreezeTime(){};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	float ComputeGameTime(float prev_time);
};

#endif _FreezeTime