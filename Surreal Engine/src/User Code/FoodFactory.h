// FoodFactory

#ifndef _FoodFactory
#define _FoodFactory

#include "FoodPool.h"
#include "Matrix.h"

class GameObject;

class FoodFactory
{
private:
	static FoodFactory* ptrInstance;

	FoodFactory();
	FoodFactory(const FoodFactory&) = delete;
	FoodFactory& operator=(const FoodFactory&) = delete;
	~FoodFactory() = default;

	static FoodFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new FoodFactory();
		return *ptrInstance;
	};

	FoodPool myFoodPool;  // Back to be a non-static member instance

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time 
	void privCreateFood(Matrix pos);
	void privRecycleFood(GameObject* b);

public:

	// Static Methods
	static void CreateFood(Matrix pos) { Instance().privCreateFood(pos); };
	static void RecycleFood(GameObject* b) { Instance().privRecycleFood(b); };

	static void Terminate();

};


#endif _FoodFactory