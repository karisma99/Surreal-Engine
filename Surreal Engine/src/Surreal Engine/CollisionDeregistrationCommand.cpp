//CollisionDeregistrationCommand

#include "CollisionDeregistrationCommand.h"
#include "CollidableAttorney.h"


CollisionDeregistrationCommand::CollisionDeregistrationCommand(Collidable* up)
{
	pCollide = up;
}

void CollisionDeregistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneDeregistration(pCollide);
}