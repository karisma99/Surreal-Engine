//CollidableGroup

#include "CollidableGroup.h"
#include "SceneAttorney.h"

void CollidableGroup::Register(Collidable* col, CollidableCollectionRef& ref)
{
	ref = CollideCol.insert(CollideCol.end(), col);
}

void CollidableGroup::Deregister(const CollidableCollectionRef& ref)
{
	CollideCol.erase(ref);
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return this->CollideCol;
}