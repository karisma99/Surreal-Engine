// HydraFactory

#include "HydraFactory.h"
#include "HydraPool.h"
#include "Hydra.h"
#include "HydraManager.h"

HydraFactory* HydraFactory::ptrInstance = nullptr;

HydraFactory::HydraFactory()
{

}

void HydraFactory::privCreateHydra(Matrix pos)
{
	Hydra* b = myHydraPool.GetHydra();

	b->Initialize(pos);
}

void HydraFactory::privRecycleHydra(GameObject* b)
{
	myHydraPool.ReturnHydra(static_cast<Hydra*>(b));
	HydraManager::ReturnHydra();
}

void HydraFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


