//FishManager

#include "FishManager.h"
#include "../Surreal Engine/SurrealSprite.h"
#include "../Surreal Engine/SceneManager.h"
#include "../User Code/SceneTwo.h"
#include "../User Code/SceneOne.h"

FishManager* FishManager::ptrInstance = nullptr;

FishManager::FishManager()
{
	currentHearts = maxHearts;
}

void FishManager::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

void FishManager::privLoseHeart()
{
	currentHearts--; 
	if (currentHearts <= 0)
	{
		privNoHearts();
	}
}

int FishManager::privGetHeartCount()
{
	return currentHearts;
}

void FishManager::privNoHearts()
{
	SceneManager::SetNextScene(new SceneTwo());
}

void FishManager::privGainHeart()
{
	currentHearts++;
	if (currentHearts >= 3)
	{
		SceneManager::SetNextScene(new SceneOne());
	}
}

void FishManager::privSetHearts(int hearts)
{
	currentHearts = hearts;
}


