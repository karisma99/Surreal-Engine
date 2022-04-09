#ifndef _CollisionTestPairCommand
#define _CollisionTestPairCommand

#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

class CollidableManager;
class CollisionDispatchBase; 

class CollisionTestPairCommand : public CollisionTestCommandBase
{
public:
	CollisionTestPairCommand() = default;
	CollisionTestPairCommand(CollidableGroup* g1, CollidableGroup* g2, CollisionDispatchBase* pd);
	CollisionTestPairCommand(const CollisionTestPairCommand& c) = delete;
	CollisionTestPairCommand& operator = (const CollisionTestPairCommand& t) = delete;
	~CollisionTestPairCommand();

	virtual void Execute();

private:

	CollidableGroup* pG1;
	CollidableGroup* pG2;
	CollisionDispatchBase* pDispatch;

};

#endif _CollisionTestPairCommand