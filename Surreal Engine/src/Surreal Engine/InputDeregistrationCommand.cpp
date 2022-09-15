#include "InputDeregistrationCommand.h"
#include "InputableAttorney.h"
#include "Keyboard.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* up, SURREAL_KEY k, EventType e)
{
	pInput = up;
	key = k;
	eventType = e;
}

void InputDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneDeregistration(pInput, key, eventType);
}