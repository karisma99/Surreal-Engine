//GameObject

#include "GameObject.h"
#include "SceneManager.h"
#include "SceneAttorney.h"

GameObject::GameObject()
{
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
	pEntryCmd = new GameObjectEntryCommand(this);
	pExitCmd = new GameObjectExitCommand(this);
}

GameObject::~GameObject()
{
	delete pEntryCmd;
	pEntryCmd = nullptr;

	delete pExitCmd;
	pExitCmd = nullptr;
}

void GameObject::ConnectToScene()
{
	assert(CurrState == RegistrationState::PENDING_REGISTRATION);
	this->SceneEntry();
	CurrState = RegistrationState::CURRENTLY_REGISTERED;
}

void GameObject::DisconnectFromScene()
{
	assert(CurrState == RegistrationState::PENDING_DEREGISTRATION);
	this->SceneExit();
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void GameObject::SceneEntry()
{
	//Overwritten
}

void GameObject::SceneExit()
{
	//Overwritten
}

void GameObject::SubmitEntry()
{
	assert(CurrState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::GameObjectReg::SubmittCommand(SceneManager::GetCurrentScene(), pEntryCmd);
	CurrState = RegistrationState::PENDING_REGISTRATION;
}

void GameObject::SubmitExit()
{
	if (CurrState == RegistrationState::CURRENTLY_REGISTERED)
	{
		SceneAttorney::GameObjectReg::SubmittCommand(SceneManager::GetCurrentScene(), pExitCmd);
		CurrState = RegistrationState::PENDING_DEREGISTRATION;
	}
}