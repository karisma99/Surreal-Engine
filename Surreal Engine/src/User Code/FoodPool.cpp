
#include "FoodPool.h"
#include "Food.h"

FoodPool::FoodPool()
{

}

FoodPool::~FoodPool()
{
	DebugMsg::out("Deleting Food\n");

	while (!createdItems.empty())
	{
		delete createdItems.front();
		createdItems.pop();
	}
}

Food* FoodPool::GetFood()
{
	Food* b;

	if (recycledItems.empty())
	{
		DebugMsg::out("New Food\n");
		b = new Food();
		createdItems.push(b);
	}
	else
	{
		DebugMsg::out("Recycled Food\n");

		b = recycledItems.top();
		recycledItems.pop();
	}
	return b;
}

void FoodPool::ReturnFood(Food* b)
{
	recycledItems.push(static_cast<Food*>(b));
	DebugMsg::out("Recycled Food\n");

}