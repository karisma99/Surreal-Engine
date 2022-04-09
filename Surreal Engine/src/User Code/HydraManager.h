// HydraManager

#ifndef _HydraManager
#define _HydraManager

#include "AzulCore.h"

class Hydra;
class Fish;

class HydraManager
{
	friend class SceneOne;
private:
	static HydraManager* ptrInstance;

	HydraManager();
	HydraManager(const HydraManager& c) = delete;
	HydraManager& operator = (const HydraManager& t) = delete;
	~HydraManager() = default;

	static HydraManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new HydraManager;
		return *ptrInstance;
	};

public:
	static void StartHydras(Fish* pPlayer) { Instance().privStartHydras(pPlayer); };
	static void SpawnHydra() { Instance().privSpawnHydra(); };
	static void ReturnHydra() { Instance().privReturnHydra(); };
	static Matrix GetPlayerPosition() { return Instance().privGetPlayerPosition(); };

private:
	void privDelete();
	static void Delete() { Instance().privDelete(); };

	void privStartHydras(Fish* pPlayer);
	void privSpawnHydra();
	void privReturnHydra();
	Matrix privGetPlayerPosition(); 

	float currentTime; 
	float lastSpawn;
	float spawnTime = 3;
	int liveHydras;
	int maxHydra = 10;
	Fish* pPlayer;

};

#endif _HydraManager