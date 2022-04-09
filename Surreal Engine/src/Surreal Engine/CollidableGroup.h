#ifndef _CollidableGroup
#define _CollidableGroup

#include <list>

class Collidable; 
class CollidableManager;

class CollidableGroup
{
public:
	using CollidableCollection = std::list<Collidable*>;

	CollidableGroup() = default;
	CollidableGroup(const CollidableGroup& c) = delete;
	CollidableGroup& operator = (const CollidableGroup& t) = delete;
	virtual ~CollidableGroup() = default;

	using CollidableCollectionRef = CollidableCollection::iterator;

	void Register(Collidable* c, CollidableCollectionRef& ref);
	void Deregister(const CollidableCollectionRef& ref);
	const CollidableCollection& GetColliderCollection();



private: 
	CollidableCollection CollideCol;

};

#endif _CollidableGroup