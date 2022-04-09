//AlarmDeregistrationCommand

#include "AlarmDeregistrationCommand.h"
#include "AlarmableAttorney.h"


AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* up, AlarmableManager::AlarmID id)
{
	pAlarm = up;
	AlarmID = id;
}

void AlarmRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::AlarmRegistration(pAlarm, AlarmID);
}