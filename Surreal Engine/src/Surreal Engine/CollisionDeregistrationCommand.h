#ifndef _CollisionDeregistrationCommand
#define _CollisionDeregistrationCommand

#include "CommandBase.h"
#include "Collidable.h"

class CollideableManager;

class CollisionDeregistrationCommand : public CommandBase
{
public:
	CollisionDeregistrationCommand() = default;
	CollisionDeregistrationCommand(Collidable* up);
	CollisionDeregistrationCommand(const CollisionDeregistrationCommand& c) = delete;
	CollisionDeregistrationCommand& operator = (const CollisionDeregistrationCommand& t) = delete;
	~CollisionDeregistrationCommand() = default;

	virtual void Execute();

private:

	Collidable* pCollide;

};

#endif CollisionDeregistrationCommand