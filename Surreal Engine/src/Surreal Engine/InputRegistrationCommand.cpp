#include "InputRegistrationCommand.h"
#include "InputableAttorney.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* up, AZUL_KEY k, EventType e)
{
	pInput = up; 
	key = k; 
	eventType = e;
}

void InputRegistrationCommand::Execute()
{
	InputableAttorney::Registration::SceneRegistration(pInput, key, eventType);
}