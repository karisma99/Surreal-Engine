#ifndef _AlarmableManager
#define _AlarmableManager

#include <map>

class Alarmable;

class AlarmableManager
{
public:
	enum AlarmID {
		Alarm0, 
		Alarm1, 
		Alarm2 
	};
	static const int NumAlarms = 3;

private:
	using AlarmEvent = std::pair<Alarmable*, AlarmID>;
	using TimelineMap = std::multimap<float, AlarmEvent>;
	TimelineMap timeline;

public:
	using StorageListRef = TimelineMap::iterator;

	AlarmableManager() = default;
	AlarmableManager(const AlarmableManager& c) = delete;
	AlarmableManager& operator = (const AlarmableManager& t) = delete;
	~AlarmableManager() = default;

	void ProcessAlarms();
	StorageListRef Register(Alarmable* up, AlarmID id, float t, StorageListRef ref);
	void Deregister(const StorageListRef& ref);

};

#endif _AlarmableManager