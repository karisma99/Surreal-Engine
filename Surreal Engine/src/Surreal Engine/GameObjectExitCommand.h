#ifndef _GameObjectExitCommand
#define _GameObjectExitCommand

#include "CommandBase.h"
#include "GameObject.h"

class GameObject;

class GameObjectExitCommand : public CommandBase
{
public:
	GameObjectExitCommand() = default;
	GameObjectExitCommand(GameObject* up);
	GameObjectExitCommand(const GameObjectExitCommand& c) = delete;
	GameObjectExitCommand& operator = (const GameObjectExitCommand& t) = delete;
	~GameObjectExitCommand() = default;

	virtual void Execute();

private:

	GameObject* pGameObject;

};

#endif _GameObjectExitCommand