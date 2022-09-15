#ifndef _CollisionTerrainCommand
#define _CollisionTerrainCommand

#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

class CollidableManager;

class CollisionTerrainCommand : public CollisionTestCommandBase
{
public:
	CollisionTerrainCommand() = default;
	CollisionTerrainCommand(CollidableGroup* g);
	CollisionTerrainCommand(const CollisionTerrainCommand& c) = delete;
	CollisionTerrainCommand& operator = (const CollisionTerrainCommand& t) = delete;
	~CollisionTerrainCommand();

	virtual void Execute();

private:

	CollidableGroup* pG;

};

#endif _CollisionTerrainCommand