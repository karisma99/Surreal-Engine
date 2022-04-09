#ifndef _AlarmableAttorney
#define _AlarmableAttorney

// AlarmableAttorney.h

#include "Alarmable.h"
#include "AlarmableManager.h"

class AlarmableAttorney
{
public:
	class GameLoop
	{
		friend class AlarmableManager;

	private:
		static void TriggerAlarm(Alarmable* p, AlarmableManager::AlarmID id) { p->TriggerAlarm(id); }
	};

public:
	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeregistrationCommand;

	private:
		static void AlarmRegistration(Alarmable* p, AlarmableManager::AlarmID id) { p->AlarmRegistration(id); }
		static void AlarmDeregistration(Alarmable* p, AlarmableManager::AlarmID id) { p->AlarmDegregistration(id); }
	};

public: 
	class theScene
	{
		friend class Scene; 
	private:
		static void SetDeleteRef(Alarmable* p, AlarmableManager::AlarmID id, AlarmableManager::StorageListRef ref) { p->SetDeleteRef(id, ref); }
	};
};

#endif _AlarmableAttorney