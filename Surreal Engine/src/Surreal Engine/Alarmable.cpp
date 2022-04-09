//Alarmable

#include "Alarmable.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < AlarmableManager::NumAlarms; i++)
	{
		RegData[i].CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
		RegData[i].pRegisterCmd = new AlarmRegistrationCommand(this, static_cast<AlarmableManager::AlarmID>(i));
		RegData[i].pDeregisterCmd = new AlarmDeregistrationCommand(this, static_cast<AlarmableManager::AlarmID>(i));
	}
}

Alarmable::~Alarmable()
{
	for (int i = 0; i < AlarmableManager::NumAlarms; i++)
	{
		delete RegData[i].pRegisterCmd;
		RegData[i].pRegisterCmd = nullptr;
		delete RegData[i].pDeregisterCmd;
		RegData[i].pDeregisterCmd = nullptr;
	}
}

void Alarmable::Alarm0()
{

}

void Alarmable::Alarm1()
{

}

void Alarmable::Alarm2()
{

}

void Alarmable::TriggerAlarm(AlarmableManager::AlarmID id)
{
	RegData[id].CurrState = RegistrationState::CURRENTLY_DEREGISTERED; 

	switch (id)
	{
	case AlarmableManager::AlarmID::Alarm0:
		Alarm0();
		break;
	case AlarmableManager::AlarmID::Alarm1:
		Alarm1();
		break;
	case AlarmableManager::AlarmID::Alarm2:
		Alarm2();
		break;
	default:
		break;
	}
}

void Alarmable::AlarmRegistration(AlarmableManager::AlarmID id)
{
	assert(RegData[id].CurrState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::AlarmableReg::Register(SceneManager::GetCurrentScene(), this, id, RegData[id].AlarmTime, RegData[id].pMyDeleteRef);
	RegData[id].CurrState = RegistrationState::CURRENTLY_REGISTERED;
}

void Alarmable::AlarmDegregistration(AlarmableManager::AlarmID id)
{
	assert(RegData[id].CurrState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::AlarmableReg::Deregister(SceneManager::GetCurrentScene(), RegData[id].pMyDeleteRef);
	RegData[id].CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Alarmable::SubmitAlarmRegistration(AlarmableManager::AlarmID id, float t)
{
	assert(RegData[id].CurrState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::AlarmableReg::SubmittCommand(SceneManager::GetCurrentScene(), RegData[id].pRegisterCmd);
	RegData[id].AlarmTime = t;
	RegData[id].CurrState = RegistrationState::PENDING_REGISTRATION;
}

void Alarmable::SubmitAlarmDeregistration(AlarmableManager::AlarmID id)
{
	assert(RegData[id].CurrState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::AlarmableReg::SubmittCommand(SceneManager::GetCurrentScene(), RegData[id].pDeregisterCmd);
	RegData[id].CurrState = RegistrationState::PENDING_DEREGISTRATION;
}

void Alarmable::SetDeleteRef(AlarmableManager::AlarmID id, AlarmableManager::StorageListRef ref)
{
	RegData[id].pMyDeleteRef = ref;
}