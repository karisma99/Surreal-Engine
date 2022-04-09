//HydraManager

#include "HydraManager.h"
#include "HydraFactory.h"
#include "Fish.h"
#include "../Surreal Engine/TimeManager.h"

HydraManager* HydraManager::ptrInstance = nullptr;

HydraManager::HydraManager()
{
	currentTime = 0; 
	lastSpawn = 0; 
	liveHydras = 0; 
	pPlayer = nullptr;
}

void HydraManager::privDelete()
{
	HydraFactory::Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}

void HydraManager::privStartHydras(Fish* player)
{
	pPlayer = player;
	liveHydras = 0;
	currentTime = TimeManager::GetTime();
}

void HydraManager::privSpawnHydra()
{
	currentTime = TimeManager::GetTime();
	
	if (currentTime - lastSpawn > spawnTime && liveHydras < maxHydra)
	{
		int x = rand() % 100 - 100; 
		int z = rand() % 100 - 100;

		HydraFactory::CreateHydra(Matrix(TRANS, Vect((float)x, 20, (float)z)));
		liveHydras++;
		lastSpawn = currentTime;
	}
}

Matrix HydraManager::privGetPlayerPosition()
{
	return pPlayer->GetPosition();
}

void HydraManager::privReturnHydra()
{
	liveHydras--;
}


