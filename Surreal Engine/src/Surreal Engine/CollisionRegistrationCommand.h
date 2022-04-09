#ifndef _CollisionRegistrationCommand
#define _CollisionRegistrationCommand

#include "CommandBase.h"
#include "Collidable.h"

class CollidableManager;

class CollisionRegistrationCommand : public CommandBase
{
public:
	CollisionRegistrationCommand() = default;
	CollisionRegistrationCommand(Collidable* up);
	CollisionRegistrationCommand(const CollisionRegistrationCommand& c) = delete;
	CollisionRegistrationCommand& operator = (const CollisionRegistrationCommand& t) = delete;
	~CollisionRegistrationCommand() = default;

	virtual void Execute();

private:

	Collidable* pCollide;

};

#endif _CollisionRegistrationCommand