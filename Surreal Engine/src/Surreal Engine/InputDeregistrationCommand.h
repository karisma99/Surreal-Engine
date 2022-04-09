#ifndef _InputDeregistrationCommand
#define _InputDeregistrationCommand

#include "CommandBase.h"
#include "Inputable.h"
#include "AzulCore.h"
#include "EventType.h"

class KeyboardEventManager;

class InputDeregistrationCommand : public CommandBase
{
public:
	InputDeregistrationCommand() = default;
	InputDeregistrationCommand(Inputable* up, AZUL_KEY k, EventType e);
	InputDeregistrationCommand(const InputDeregistrationCommand& c) = delete;
	InputDeregistrationCommand& operator = (const InputDeregistrationCommand& t) = delete;
	~InputDeregistrationCommand() = default;

	virtual void Execute();

private:

	Inputable* pInput;
	AZUL_KEY key;
	EventType eventType;

};

#endif _InputDeregistrationCommand