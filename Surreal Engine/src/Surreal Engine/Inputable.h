#ifndef _Inputable
#define _Inputable

#include "RegistrationState.h"
#include "KeyBoardEventManager.h"
#include "SingleKeyEventManager.h"
#include "InputRegistrationCommand.h"
#include "InputDeregistrationCommand.h"
#include "KeyboardEventManager.h"
#include "SingleKeyEventManager.h"

class InputRegistrationCommand;
class InputDeregistrationCommand;

class Inputable
{
	friend class InputableAttorney;

public:
	Inputable() = default;
	Inputable(const Inputable& c) = delete;
	Inputable& operator = (const Inputable& t) = delete;
	virtual ~Inputable();

	void SubmitKeyRegistration(AZUL_KEY k, EventType e);
	void SubmitKeyDeregistration(AZUL_KEY k, EventType e);

private:
	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);

	void InputRegistration(AZUL_KEY k, EventType e);
	void InputDegregistration(AZUL_KEY k, EventType e);

	void SetSingleDeleteRef(AZUL_KEY k, EventType e, SingleKeyEventManager::InputableCollectionRef ref);
	void SetKeyboardDeleteRef(AZUL_KEY k, EventType e, KeyboardEventManager::StorageListRef ref);

	struct RegistrationData
	{
		RegistrationState CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
		InputRegistrationCommand* pRegisterCmd;
		InputDeregistrationCommand* pDeregisterCmd;
		KeyboardEventManager::StorageListRef pMyDeleteKeyboardRef;
		SingleKeyEventManager::InputableCollectionRef pMyDeleteSingleRef;
	};

	using KeyEvent = std::pair<AZUL_KEY, EventType>;
	using InputableKeys = std::map<KeyEvent, RegistrationData>;
	InputableKeys keysMap;

	using KeysMapRef = InputableKeys::iterator;

};

#endif _Inputable