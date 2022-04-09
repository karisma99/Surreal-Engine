#ifndef _CollisionTestSelfCommand
#define _CollisionTestSelfCommand

#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

class CollidableManager;
class CollisionDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
public:
	CollisionTestSelfCommand() = default;
	CollisionTestSelfCommand(CollidableGroup* g, CollisionDispatchBase* pd);
	CollisionTestSelfCommand(const CollisionTestSelfCommand& c) = delete;
	CollisionTestSelfCommand& operator = (const CollisionTestSelfCommand& t) = delete;
	~CollisionTestSelfCommand();

	virtual void Execute();

private:

	CollidableGroup* pG;
	CollisionDispatchBase* pDispatch;

};

#endif _CollisionTestSelfCommand