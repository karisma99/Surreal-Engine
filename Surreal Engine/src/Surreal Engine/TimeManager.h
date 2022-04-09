// CameraManager.h

#ifndef _TimeManager
#define _TimeManager

#include "Surreal.h"
#include "FreezeTime.h"

class TimeManager
{
private:

	friend class TimeManagerAttorney;

	static TimeManager* ptrInstance;

	TimeManager();
	TimeManager(const TimeManager& c) = delete;
	TimeManager& operator = (const TimeManager& t) = delete;
	~TimeManager() = default;

	static TimeManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TimeManager;
		return *ptrInstance;
	};

public:
	static float GetTime() { return Instance().privGetTime(); };
	static float GetFrameTime() { return Instance().privGetFrameTime(); };

private:

	float privGetTime();
	float privGetFrameTime();

	static void ProcessTime() { Instance().privProcessTime(); };
	void privProcessTime(); 

	static void Delete() { Instance().privDelete(); };
	void privDelete();

	float PreviousTime; 
	float CurrentTime;
	float FrameTime;
	FreezeTime* pFrzTime;

};

#endif _TimeManager