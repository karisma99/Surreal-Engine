#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "CommandBase.h"
#include "Inputable.h"
#include "EventType.h"
#include "Keyboard.h"

class KeyboardEventManager;

class InputDeregistrationCommand : public CommandBase
{
public:
	InputDeregistrationCommand() = default;
	InputDeregistrationCommand(Inputable* up, SURREAL_KEY k, EventType e);
	InputDeregistrationCommand(const InputDeregistrationCommand& c) = delete;
	InputDeregistrationCommand& operator = (const InputDeregistrationCommand& t) = delete;
	~InputDeregistrationCommand() = default;

	virtual void Execute();

private:

	Inputable* pInput;
	SURREAL_KEY key;
	EventType eventType;

};

#endif _InputDeregistrationCommand