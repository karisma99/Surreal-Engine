//SceneTwo

#include "SceneTwo.h"
#include "../User Code/World2.h"
#include "../User Code/Fish.h"
#include "../User Code/Hydra.h"
#include "../User Code/GodCam.h"
#include "../User Code/BubbleManager.h"
#include "../User Code/Bubble.h"
#include "../User Code/Hud2.h"
#include "../User Code/FoodManager.h"
#include "../User Code/FishManager.h"
#include "../User Code/Food.h"

void SceneTwo::Initialize()
{
	pWorld = new World2();
	pFish = new Fish();
	FishManager::SetHearts(0);
	pHud = new Hud2();
	pGodCam = new GodCam();

	FoodManager::StartFood(); //Start food spawn

	SetCollisionPair<Fish, Food>();
}

void SceneTwo::SceneEnd()
{
	FoodManager::Delete();
	BubbleManager::Delete();
	FishManager::Delete();

	delete pWorld;
	pWorld = nullptr;

	delete pFish;
	pFish = nullptr;

	delete pHud;

	delete pGodCam;
	pGodCam = nullptr;
}
