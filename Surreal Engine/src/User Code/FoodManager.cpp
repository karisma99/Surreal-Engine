//FoodManager

#include "FoodManager.h"
#include "FoodFactory.h"
#include "Food.h"
#include "../Surreal Engine/TimeManager.h"
#include "../User Code/FishManager.h"

FoodManager* FoodManager::ptrInstance = nullptr;

FoodManager::FoodManager()
{
	currentTime = 0;
	lastSpawn = 0;
	liveHydras = 0;
	foodEaten = 0;
}

void FoodManager::privDelete()
{
	FoodFactory::Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}

void FoodManager::privStartFood()
{
	liveHydras = 0;
	currentTime = TimeManager::GetTime();
}

void FoodManager::privSpawnFood()
{
	currentTime = TimeManager::GetTime();

	if (currentTime - lastSpawn > spawnTime && liveHydras < maxHydra)
	{
		int x = rand() % 500 - 500;
		int z = rand() % 500 - 500;

		FoodFactory::CreateFood(Matrix(TRANS, Vect((float)x, 20, (float)z)));
		liveHydras++;
		lastSpawn = currentTime;
	}
}

void FoodManager::privReturnFood()
{
	liveHydras--;
}

void FoodManager::privEatFood()
{
	foodEaten++; 
	if (foodEaten >= foodNeeded)
	{
		FishManager::GainHeart();
	}
}

int FoodManager::privGetFoodEatenCount()
{
	return foodEaten;
}


