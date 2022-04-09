// FoodFactory

#include "FoodFactory.h"
#include "FoodPool.h"
#include "Food.h"
#include "FoodManager.h"

FoodFactory* FoodFactory::ptrInstance = nullptr;

FoodFactory::FoodFactory()
{

}

void FoodFactory::privCreateFood(Matrix pos)
{
	Food* b = myFoodPool.GetFood();

	b->Initialize(pos);
}

void FoodFactory::privRecycleFood(GameObject* b)
{
	myFoodPool.ReturnFood(static_cast<Food*>(b));
	FoodManager::ReturnFood();
}

void FoodFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


