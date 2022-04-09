#ifndef _AlarmDeregistrationCommand
#define _AlarmDeregistrationCommand

#include "CommandBase.h"
#include "Alarmable.h"
#include "AlarmableManager.h"

class AlarmableManager;

class AlarmDeregistrationCommand : public CommandBase
{
public:
	AlarmDeregistrationCommand() = default;
	AlarmDeregistrationCommand(Alarmable* up, AlarmableManager::AlarmID id);
	AlarmDeregistrationCommand(const AlarmDeregistrationCommand& c) = delete;
	AlarmDeregistrationCommand& operator = (const AlarmDeregistrationCommand& t) = delete;
	~AlarmDeregistrationCommand() = default;

	virtual void Execute();

private:

	Alarmable* pAlarm;
	AlarmableManager::AlarmID AlarmID;

};

#endif _AlarmDeregistrationCommand