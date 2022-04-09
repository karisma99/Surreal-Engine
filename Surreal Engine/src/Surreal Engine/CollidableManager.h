#ifndef _CollidableManager
#define _CollidableManager

#include "CollidableGroup.h"
#include "CollisionTestCommandBase.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestSelfCommand.h"
#include "CollisionDispatch.h"
#include <vector>

class Collidable;
class CollidableGroup;
class CollisionTestCommandBase; 
class CollisionTestPairCommand; 
class CollisionTestSelfCommand; 

class CollidableManager
{
public:
	using STypeID = int;
	static const STypeID SID_UNDEFINED = -1;

private:
	using CollidableGroupCollection = std::vector<CollidableGroup*>;
	CollidableGroupCollection ColGroupCollection;

	using CollisionTestCommands = std::list<CollisionTestCommandBase*>;
	CollisionTestCommands colTestCommands;

	void SetGroupForTypeID(CollidableManager::STypeID ind);

	static STypeID TypeIDNextNumber;
	const int MAX_GROUP_COLLECTION = 250;

public:
	CollidableManager();
	CollidableManager(const CollidableManager& c) = delete;
	CollidableManager& operator = (const CollidableManager& t) = delete;
	~CollidableManager();

	using CollidableGroupRef = CollidableGroupCollection::iterator;

	template<typename C>
	STypeID GetTypeID()
	{
		static STypeID myTypeID = TypeIDNextNumber++;

		SetGroupForTypeID(myTypeID);

		return myTypeID;
	}

	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];
		CollidableGroup* pg2 = ColGroupCollection[GetTypeID<C2>()];

		CollisionDispatch<C1, C2>* pDispatch = new CollisionDispatch<C1, C2>();

		colTestCommands.push_back(new CollisionTestPairCommand(pg1, pg2, pDispatch));
	}

	template<typename C1>
	void SetCollisionSelf()
	{
		CollidableGroup* pg1 = ColGroupCollection[GetTypeID<C1>()];

		CollisionDispatch<C1, C1>* pDispatch = new CollisionDispatch<C1, C1>();

		colTestCommands.push_back(new CollisionTestSelfCommand(pg1, pDispatch));
	}

	CollidableGroup* GetColGroup(STypeID id);
	void ProcessCollisions();

};

#endif _CollidableManager