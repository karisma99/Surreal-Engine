#ifndef _Alarmable
#define _Alarmable

#include "RegistrationState.h"
#include "AlarmableManager.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeregistrationCommand.h"

class AlarmableManager;
class AlarmRegistrationCommand;
class AlarmDeregistrationCommand;

class Alarmable
{
	friend class AlarmableAttorney;

public:
	Alarmable();
	Alarmable(const Alarmable& c) = delete;
	Alarmable& operator = (const Alarmable& t) = delete;
	virtual ~Alarmable();

	void SubmitAlarmRegistration(AlarmableManager::AlarmID i, float t);
	void SubmitAlarmDeregistration(AlarmableManager::AlarmID id);

private:
	virtual void Alarm0();
	virtual void Alarm1();
	virtual void Alarm2();

	void TriggerAlarm(AlarmableManager::AlarmID id);

	void AlarmRegistration(AlarmableManager::AlarmID id);
	void AlarmDegregistration(AlarmableManager::AlarmID id);

	void SetDeleteRef(AlarmableManager::AlarmID id, AlarmableManager::StorageListRef);

	struct RegistrationData
	{
		RegistrationState CurrState;
		AlarmRegistrationCommand* pRegisterCmd;
		AlarmDeregistrationCommand* pDeregisterCmd;
		AlarmableManager::StorageListRef pMyDeleteRef;
		float AlarmTime;
	};

	RegistrationData RegData[AlarmableManager::NumAlarms];

};

#endif _Drawable