#ifndef _InputRegistrationCommand
#define _InputRegistrationCommand

#include "CommandBase.h"
#include "Inputable.h"
#include "EventType.h"

class Inputable;
class KeyboardEventManager;

class InputRegistrationCommand : public CommandBase
{
public:
	InputRegistrationCommand() = default;
	InputRegistrationCommand(Inputable* up, SURREAL_KEY k, EventType e);
	InputRegistrationCommand(const InputRegistrationCommand& c) = delete;
	InputRegistrationCommand& operator = (const InputRegistrationCommand& t) = delete;
	~InputRegistrationCommand() = default;

	virtual void Execute();

private:

	Inputable* pInput;
	SURREAL_KEY key;
	EventType eventType;

};

#endif _InputRegistrationCommand