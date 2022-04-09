// FoodPool

#ifndef _FoodPool
#define _FoodPool

#include <stack>
#include <queue>
class Food;

class FoodPool
{
private:
	std::stack<Food*> recycledItems;
	std::queue<Food*> createdItems;

public:
	FoodPool();
	FoodPool(const FoodPool&) = delete;
	FoodPool& operator=(const FoodPool&) = delete;
	~FoodPool();

	Food* GetFood();

	void ReturnFood(Food* b);
};


#endif _FoodPool