#ifndef _UpdateDeregistrationCommand
#define _UpdateDeregistrationCommand

#include "CommandBase.h"
#include "Updateable.h"

class UpdateableManager;
class Updateable;

class UpdateDeregistrationCommand : public CommandBase
{
public:
	UpdateDeregistrationCommand() = default;
	UpdateDeregistrationCommand(Updateable* up);
	UpdateDeregistrationCommand(const UpdateDeregistrationCommand& c) = delete;
	UpdateDeregistrationCommand& operator = (const UpdateDeregistrationCommand& t) = delete;
	~UpdateDeregistrationCommand() = default;

	virtual void Execute();

private:

	Updateable* pUpdate;

};

#endif _UpdateRegistrationCommand