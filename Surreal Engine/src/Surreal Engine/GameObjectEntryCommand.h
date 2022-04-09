#ifndef _GameObjectEntryCommand
#define _GameObjectEntryCommand

#include "CommandBase.h"
#include "GameObject.h"

class GameObject;

class GameObjectEntryCommand : public CommandBase
{
public:
	GameObjectEntryCommand() = default;
	GameObjectEntryCommand(GameObject* up);
	GameObjectEntryCommand(const GameObjectEntryCommand& c) = delete;
	GameObjectEntryCommand& operator = (const GameObjectEntryCommand& t) = delete;
	~GameObjectEntryCommand() = default;

	virtual void Execute();

private:

	GameObject* pGameObject;

};

#endif _GameObjectEntryCommand