
#include "HydraPool.h"
#include "Hydra.h"

HydraPool::HydraPool()
{

}

HydraPool::~HydraPool()
{
	DebugMsg::out("Deleting Hydra\n");

	while (!createdItems.empty())
	{
		delete createdItems.front();
		createdItems.pop();
	}
}

Hydra* HydraPool::GetHydra()
{
	Hydra* b;

	if (recycledItems.empty())
	{
		DebugMsg::out("New Hydra\n");
		b = new Hydra();
		createdItems.push(b);
	}
	else
	{
		DebugMsg::out("Recycled Hydra\n");

		b = recycledItems.top();
		recycledItems.pop();
	}
	
	return b;
}

void HydraPool::ReturnHydra(Hydra* b)
{
	recycledItems.push(static_cast<Hydra*>(b));
	DebugMsg::out("Recycled Hydra\n");

}