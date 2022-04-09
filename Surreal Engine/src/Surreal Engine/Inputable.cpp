//Inputable

#include "Inputable.h"
#include "SceneAttorney.h"
#include "SceneManager.h"

Inputable::~Inputable()
{
	for (auto& it : keysMap)
	{
		delete it.second.pRegisterCmd;
		it.second.pRegisterCmd = nullptr;
		delete it.second.pDeregisterCmd;
		it.second.pDeregisterCmd = nullptr;
	}
}

void Inputable::KeyPressed(AZUL_KEY k)
{
	//Overwritten
	k;
}

void Inputable::KeyReleased(AZUL_KEY k)
{
	//Overwritten
	k;
}

void Inputable::InputRegistration(AZUL_KEY k, EventType e)
{
	KeysMapRef ref = keysMap.find(std::pair<AZUL_KEY, EventType>(k, e));
	assert(ref->second.CurrState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::InputableReg::Register(SceneManager::GetCurrentScene(), this, k, e, ref->second.pMyDeleteKeyboardRef, ref->second.pMyDeleteSingleRef);
	ref->second.CurrState = RegistrationState::CURRENTLY_REGISTERED;
}

void Inputable::InputDegregistration(AZUL_KEY k, EventType e)
{
	KeysMapRef ref = keysMap.find(std::pair<AZUL_KEY, EventType>(k, e));
	assert(ref->second.CurrState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::InputableReg::Deregister(SceneManager::GetCurrentScene(), e, ref->second.pMyDeleteKeyboardRef, ref->second.pMyDeleteSingleRef);
	ref->second.CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Inputable::SubmitKeyRegistration(AZUL_KEY k, EventType e)
{
	//Check if already exists in list
	KeysMapRef ref = keysMap.find(std::pair<AZUL_KEY, EventType>(k, e));

	if (ref == keysMap.end())
	{
		RegistrationData RegData;
		RegData.pRegisterCmd = new InputRegistrationCommand(this, k, e); 
		RegData.pDeregisterCmd = new InputDeregistrationCommand(this, k, e); 
		ref = keysMap.insert(keysMap.end(), std::pair<KeyEvent, RegistrationData>(std::pair<AZUL_KEY, EventType>(k, e), RegData));
	}

	assert(ref != keysMap.end());
	assert(ref->second.CurrState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::InputableReg::SubmittCommand(SceneManager::GetCurrentScene(), ref->second.pRegisterCmd);
	ref->second.CurrState = RegistrationState::PENDING_REGISTRATION;
}

void Inputable::SubmitKeyDeregistration(AZUL_KEY k, EventType e)
{
	KeysMapRef ref = keysMap.find(std::pair<AZUL_KEY, EventType>(k, e));
	assert(ref->second.CurrState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::InputableReg::SubmittCommand(SceneManager::GetCurrentScene(), ref->second.pDeregisterCmd);
	ref->second.CurrState = RegistrationState::PENDING_DEREGISTRATION;
}

void Inputable::SetKeyboardDeleteRef(AZUL_KEY k, EventType e, KeyboardEventManager::StorageListRef ref)
{
	KeysMapRef it = keysMap.find(std::pair<AZUL_KEY, EventType>(k, e));
	it->second.pMyDeleteKeyboardRef = ref;
}

void Inputable::SetSingleDeleteRef(AZUL_KEY k, EventType e, SingleKeyEventManager::InputableCollectionRef ref)
{
	KeysMapRef it = keysMap.find(std::pair<AZUL_KEY, EventType>(k, e));
	it->second.pMyDeleteSingleRef = ref;
}