//Updateable

#include "Updateable.h"
#include "SceneManager.h"
#include "CommandBase.h"
#include "SceneAttorney.h"

Updateable::Updateable()
{
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegisterCmd = new UpdateRegistrationCommand(this);
	pDeregisterCmd = new UpdateDeregistrationCommand(this);
}

Updateable::~Updateable()
{
	delete pRegisterCmd;
	pRegisterCmd = nullptr;

	delete pDeregisterCmd;
	pDeregisterCmd = nullptr;
}

void Updateable::Update()
{
	
}

void Updateable::SceneRegistration()
{
	assert(CurrState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::UpdateableReg::Register(SceneManager::GetCurrentScene(), this, pMyDeleteRef);
	CurrState = RegistrationState::CURRENTLY_REGISTERED;
}

void Updateable::SceneDegregistration()
{
	assert(CurrState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::UpdateableReg::Deregister(SceneManager::GetCurrentScene(), pMyDeleteRef);
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Updateable::SubmitUpdateRegistration()
{
	assert(CurrState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::UpdateableReg::SubmittCommand(SceneManager::GetCurrentScene(), pRegisterCmd);
	CurrState = RegistrationState::PENDING_REGISTRATION;
}

void Updateable::SubmitUpdateDeregistration()
{
	assert(CurrState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::UpdateableReg::SubmittCommand(SceneManager::GetCurrentScene(), pDeregisterCmd);
	CurrState = RegistrationState::PENDING_DEREGISTRATION;
}