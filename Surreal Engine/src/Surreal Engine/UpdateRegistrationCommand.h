#ifndef _UpdateRegistrationCommand
#define _UpdateRegistrationCommand

#include "CommandBase.h"
#include "Updateable.h"

class UpdateableManager;
class Updateable;

class UpdateRegistrationCommand : public CommandBase
{
public:
	UpdateRegistrationCommand() = default;
	UpdateRegistrationCommand(Updateable* up);
	UpdateRegistrationCommand(const UpdateRegistrationCommand& c) = delete;
	UpdateRegistrationCommand& operator = (const UpdateRegistrationCommand& t) = delete;
	~UpdateRegistrationCommand() = default;

	virtual void Execute();

private:

	Updateable* pUpdate; 

};

#endif _UpdateRegistrationCommand