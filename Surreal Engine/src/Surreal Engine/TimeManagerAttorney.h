//TimeManagerAttorney.h

#include "TimeManager.h"

class TimeManagerAttorney
{
	friend class Surreal;
private:
	static void ProcessTime() { TimeManager::ProcessTime(); }
	static void Delete() { TimeManager::Delete(); }
};