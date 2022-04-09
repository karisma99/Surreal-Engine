//AlarmDeregistrationCommand

#include "AlarmDeregistrationCommand.h"
#include "AlarmableAttorney.h"


AlarmDeregistrationCommand::AlarmDeregistrationCommand(Alarmable* up, AlarmableManager::AlarmID id)
{
	pAlarm = up;
	AlarmID = id;
}

void AlarmDeregistrationCommand::Execute()
{
	AlarmableAttorney::Registration::AlarmDeregistration(pAlarm, AlarmID);
}