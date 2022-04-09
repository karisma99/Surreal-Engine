#include "InputDeregistrationCommand.h"
#include "InputableAttorney.h"

InputDeregistrationCommand::InputDeregistrationCommand(Inputable* up, AZUL_KEY k, EventType e)
{
	pInput = up;
	key = k;
	eventType = e;
}

void InputDeregistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneDeregistration(pInput, key, eventType);
}