//DrawRegistrationCommand

#include "CollisionRegistrationCommand.h"
#include "CollidableAttorney.h"


CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* up)
{
	pCollide = up;
}

void CollisionRegistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneRegistration(pCollide);
}