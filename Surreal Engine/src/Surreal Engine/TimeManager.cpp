//TimeManager

#include "TimeManager.h"
#include "SurrealAttorney.h"

TimeManager* TimeManager::ptrInstance = nullptr;

TimeManager::TimeManager()
{
	pFrzTime = new FreezeTime();
	PreviousTime = 0; 
	CurrentTime = 0; 
	FrameTime = 0;
}

void TimeManager::privProcessTime()
{
	PreviousTime = CurrentTime;

	//CurrentTime = SurrealAttorney::Time::GetTime();        // Release mode
	CurrentTime = pFrzTime->ComputeGameTime(PreviousTime);  // Debug mode

	FrameTime = CurrentTime - PreviousTime;
}

float TimeManager::privGetTime()
{
	return CurrentTime;
}

float TimeManager::privGetFrameTime()
{
	return FrameTime;
}

void TimeManager::privDelete()
{
	delete pFrzTime;
	pFrzTime = nullptr;

	delete ptrInstance;
	ptrInstance = nullptr;
}