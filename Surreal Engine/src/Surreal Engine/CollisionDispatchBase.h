#ifndef _CollisionDispatchBase
#define _CollisionDispatchBase


class Collidable; 

class CollisionDispatchBase
{
public:
	CollisionDispatchBase() { };
	CollisionDispatchBase(const CollisionDispatchBase& c) = delete;
	CollisionDispatchBase& operator = (const CollisionDispatchBase& t) = delete;
	virtual ~CollisionDispatchBase() { };

	virtual void ProcessCallbacks(Collidable* p1, Collidable* p2) { p1; p2; };
};

#endif _CollisionDispatchBase