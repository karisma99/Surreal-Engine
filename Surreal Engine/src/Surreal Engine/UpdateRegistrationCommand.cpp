//UpdateRegistrationCommand

#include "UpdateRegistrationCommand.h"
#include "UpdateableAttorney.h"


UpdateRegistrationCommand::UpdateRegistrationCommand(Updateable* up)
{
	pUpdate = up; 
}

void UpdateRegistrationCommand::Execute()
{
	UpdateableAttorney::Registration::SceneRegistration(pUpdate);
}