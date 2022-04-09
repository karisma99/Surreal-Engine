#ifndef _CollisionDispatch
#define _CollisionDispatch

#include "CollisionDispatchBase.h"

template <typename C1, typename C2>
class CollisionDispatch : public CollisionDispatchBase
{
public:

	CollisionDispatch() = default;
	CollisionDispatch(const CollisionDispatch& c) = delete;
	CollisionDispatch& operator = (const CollisionDispatch& t) = delete;
	~CollisionDispatch() = default;

	virtual void ProcessCallbacks(Collidable* p1, Collidable* p2)
	{
		C1* pDerCol1 = static_cast<C1*>(p1);
		C2* pDerCol2 = static_cast<C2*>(p2);

		pDerCol1->Collision(pDerCol2);
		pDerCol2->Collision(pDerCol1);
	}
};

#endif _CollisionDispatch