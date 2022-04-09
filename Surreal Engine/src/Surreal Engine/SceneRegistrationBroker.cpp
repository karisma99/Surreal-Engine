//SceneRegistrationBroker

#include "SceneRegistrationBroker.h"

void SceneRegistrationBroker::AddCommand(CommandBase* cmd)
{
	CommandLst.insert(CommandLst.end(), cmd);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	for (auto& it : CommandLst)
	{
		it->Execute();
	}
	
	CommandLst.clear();
}
