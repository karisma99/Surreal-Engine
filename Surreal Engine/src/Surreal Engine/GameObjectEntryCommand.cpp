//GameObjectEntryCommand

#include "GameObjectEntryCommand.h"
#include "GameObjectAttorney.h"


GameObjectEntryCommand::GameObjectEntryCommand(GameObject* up)
{
	pGameObject = up;
}

void GameObjectEntryCommand::Execute()
{
	GameObjectAttorney::Registration::SceneRegistration(pGameObject);
}