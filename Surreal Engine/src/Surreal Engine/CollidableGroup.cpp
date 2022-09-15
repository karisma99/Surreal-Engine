//CollidableGroup

#include "CollidableGroup.h"
#include "SceneAttorney.h"
#include "CollisionVolumeAABB.h"

CollidableGroup::CollidableGroup()
{
	pGroupAABB = new CollisionVolumeAABB();
}

CollidableGroup::~CollidableGroup()
{
	delete pGroupAABB;
}

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

void CollidableGroup::CalculateAABB()
{
	pGroupAABB->ComputeData(this->CollideCol);
}

CollisionVolumeAABB& CollidableGroup::GetGroupAABB()
{
	return *this->pGroupAABB;
}