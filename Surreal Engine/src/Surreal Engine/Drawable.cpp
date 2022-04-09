//Drawable

#include "Drawable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

Drawable::Drawable()
{
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegisterCmd = new DrawRegistrationCommand(this);
	pDeregisterCmd = new DrawDeregistrationCommand(this);
}

Drawable::~Drawable()
{
	delete pRegisterCmd;
	pRegisterCmd = nullptr;

	delete pDeregisterCmd;
	pDeregisterCmd = nullptr;
}

void Drawable::Draw()
{
	
}

void Drawable::Draw2D()
{

}

void Drawable::SceneRegistration()
{
	assert(CurrState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::DrawableReg::Register(SceneManager::GetCurrentScene(), this, pMyDeleteRef);
	CurrState = RegistrationState::CURRENTLY_REGISTERED;
}

void Drawable::SceneDegregistration()
{
	assert(CurrState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::DrawableReg::Deregister(SceneManager::GetCurrentScene(), pMyDeleteRef);
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Drawable::SubmitDrawRegistration()
{
	assert(CurrState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::DrawableReg::SubmittCommand(SceneManager::GetCurrentScene(), pRegisterCmd);
	CurrState = RegistrationState::PENDING_REGISTRATION;
}

void Drawable::SubmitDrawDeregistration()
{
	assert(CurrState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::DrawableReg::SubmittCommand(SceneManager::GetCurrentScene(), pDeregisterCmd);
	CurrState = RegistrationState::PENDING_DEREGISTRATION;
}