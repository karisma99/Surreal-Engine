#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include "CommandBase.h"
#include <list>

class SceneRegistrationBroker
{
public:
	void AddCommand(CommandBase* cmd);
	void ExecuteCommands();

private:
	using CommandList = std::list<CommandBase*>;
	CommandList CommandLst;
};

#endif _SceneRegistrationBroker