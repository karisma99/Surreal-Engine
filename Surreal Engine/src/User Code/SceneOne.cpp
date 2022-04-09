//SceneDemo

#include "SceneOne.h"
#include "../User Code/World.h"
#include "../User Code/Fish.h"
#include "../User Code/Hydra.h"
#include "../User Code/GodCam.h"
#include "../User Code/BubbleManager.h"
#include "../User Code/Bubble.h"
#include "../User Code/Hud.h"
#include "../User Code/HydraManager.h"
#include "../User Code/FishManager.h"

void SceneOne::Initialize()
{
	pWorld = new World();
	pFish = new Fish();
	pHud = new Hud();
	pGodCam = new GodCam();

	HydraManager::StartHydras(pFish);

	SetCollisionPair<Fish, Hydra>(); 
	SetCollisionPair<Hydra, Bubble>();
}

void SceneOne::SceneEnd()
{
	BubbleManager::Delete();
	HydraManager::Delete();
	FishManager::Delete();

	delete pWorld;
	pWorld = nullptr;

	delete pHydra;
	pHydra = nullptr;

	delete pFish;
	pFish = nullptr;

	delete pHud;

	delete pGodCam;
	pGodCam = nullptr;
}