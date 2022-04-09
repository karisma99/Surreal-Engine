//SceneChangeCommand

#include "SceneChangeCommand.h"
#include "SceneManagerAttorney.h"

SceneChangeCommand::SceneChangeCommand()
{
	pScene = nullptr;
}

SceneChangeCommand::SceneChangeCommand(Scene* s)
{
	pScene = s;
}

void SceneChangeCommand::SetScene(Scene* s)
{
	pScene = s;
}

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::Command::ChangeScene(pScene); 
}