//GameObjectExitCommand

#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"


GameObjectExitCommand::GameObjectExitCommand(GameObject* up)
{
	pGameObject = up;
}

void GameObjectExitCommand::Execute()
{
	GameObjectAttorney::Registration::SceneDeregistration(pGameObject);
}