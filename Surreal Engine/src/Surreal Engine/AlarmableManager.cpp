//AlarmableManager

#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include "TimeManager.h"

void AlarmableManager::ProcessAlarms()
{
	float currTime = TimeManager::GetTime();

	StorageListRef ref = timeline.begin();

	while (ref != timeline.end() && ref->first <= currTime)
	{
		AlarmableAttorney::GameLoop::TriggerAlarm(ref->second.first, ref->second.second);
		timeline.erase(ref);
		ref = timeline.begin();
	}
}

AlarmableManager::StorageListRef AlarmableManager::Register(Alarmable* up, AlarmID id, float t, StorageListRef ref)
{
	ref = timeline.insert(timeline.end(), std::pair<float, AlarmEvent>(t + TimeManager::GetTime(), std::pair<Alarmable*, AlarmID>(up, id)));
	return ref;
}

void AlarmableManager::Deregister(const StorageListRef& ref)
{
	timeline.erase(ref);
}
