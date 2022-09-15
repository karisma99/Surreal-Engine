//CollidableManager

#include "CollidableManager.h"

CollidableManager::STypeID CollidableManager::TypeIDNextNumber = 0;

CollidableManager::CollidableManager()
{
	for (int x = 0; x < MAX_GROUP_COLLECTION; x++)
	{
		ColGroupCollection.push_back(nullptr);
	}
}

CollidableManager::~CollidableManager()
{
	for (auto& it : ColGroupCollection)
	{
		delete it;
		it = nullptr;
	}

	for (auto& it : colTestCommands)
	{
		delete it;
		it = nullptr;
	}
}

void CollidableManager::SetGroupForTypeID(CollidableManager::STypeID ind)
{
	if (ColGroupCollection[ind] == nullptr)
	{
		ColGroupCollection[ind] = new CollidableGroup();
	}
		
}

CollidableGroup* CollidableManager::GetColGroup(CollidableManager::STypeID ind)
{
	return ColGroupCollection[ind];
}

void CollidableManager::ProcessCollisions()
{
	for (CollidableGroup* it : ColGroupCollection)
	{
		if (it)
		{
			it->CalculateAABB();
		}
		
	}

	for (CollisionTestCommands::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		(*it)->Execute();
	}

}