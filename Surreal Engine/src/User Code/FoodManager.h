// FoodManager

#ifndef _FoodManager
#define _FoodManager

#include "AzulCore.h"

class Fish;

class FoodManager
{
	friend class SceneTwo;
private:
	static FoodManager* ptrInstance;

	FoodManager();
	FoodManager(const FoodManager& c) = delete;
	FoodManager& operator = (const FoodManager& t) = delete;
	~FoodManager() = default;

	static FoodManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new FoodManager;
		return *ptrInstance;
	};

public:
	static void StartFood() { Instance().privStartFood(); };
	static void SpawnFood() { Instance().privSpawnFood(); };
	static void ReturnFood() { Instance().privReturnFood(); };
	static void EatFood() { Instance().privEatFood(); };
	static int GetGoodEatenCount() { return Instance().privGetFoodEatenCount(); };

private:
	void privDelete();
	static void Delete() { Instance().privDelete(); };

	void privStartFood();
	void privSpawnFood();
	void privReturnFood();
	void privEatFood();
	int privGetFoodEatenCount();

	float currentTime;
	float lastSpawn;
	float spawnTime = 1;
	int liveHydras;
	int maxHydra = 5;
	int foodEaten; 
	int foodNeeded = 3;

};

#endif _FoodManager