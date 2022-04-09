#ifndef _AlarmRegistrationCommand
#define _AlarmRegistrationCommand

#include "CommandBase.h"
#include "Alarmable.h"

class AlarmableManager;

class AlarmRegistrationCommand : public CommandBase
{
public:
	AlarmRegistrationCommand() = default;
	AlarmRegistrationCommand(Alarmable* up, AlarmableManager::AlarmID id);
	AlarmRegistrationCommand(const AlarmRegistrationCommand& c) = delete;
	AlarmRegistrationCommand& operator = (const AlarmRegistrationCommand& t) = delete;
	~AlarmRegistrationCommand() = default;

	virtual void Execute();

private:

	Alarmable* pAlarm;
	AlarmableManager::AlarmID AlarmID;

};

#endif _AlarmRegistrationCommand