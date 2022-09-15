#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>

class Collidable; 
class CollidableManager;
class CollisionVolumeAABB;

class CollidableGroup
{
public:
	using CollidableCollection = std::list<Collidable*>;

	CollidableGroup();
	CollidableGroup(const CollidableGroup& c) = delete;
	CollidableGroup& operator = (const CollidableGroup& t) = delete;
	~CollidableGroup();

	using CollidableCollectionRef = CollidableCollection::iterator;

	void Register(Collidable* c, CollidableCollectionRef& ref);
	void Deregister(const CollidableCollectionRef& ref);
	const CollidableCollection& GetColliderCollection();
	void CalculateAABB();
	CollisionVolumeAABB& GetGroupAABB();


private: 
	CollidableCollection CollideCol;
	CollisionVolumeAABB* pGroupAABB;

};

#endif _CollidableGroup