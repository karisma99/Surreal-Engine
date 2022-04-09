//UpdateDeregistrationCommand

#include "UpdateDeregistrationCommand.h"
#include "UpdateableAttorney.h"


UpdateDeregistrationCommand::UpdateDeregistrationCommand(Updateable* up)
{
	pUpdate = up;
}

void UpdateDeregistrationCommand::Execute()
{
	UpdateableAttorney::Registration::SceneDeregistration(pUpdate);
}