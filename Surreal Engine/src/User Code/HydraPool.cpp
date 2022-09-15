
#include "HydraPool.h"
#include "Hydra.h"

HydraPool::HydraPool()
{

}

HydraPool::~HydraPool()
{
	Trace::out("Deleting Hydra\n");

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
		Trace::out("New Hydra\n");
		b = new Hydra();
		createdItems.push(b);
	}
	else
	{
		Trace::out("Recycled Hydra\n");

		b = recycledItems.top();
		recycledItems.pop();
	}
	
	return b;
}

void HydraPool::ReturnHydra(Hydra* b)
{
	recycledItems.push(static_cast<Hydra*>(b));
	Trace::out("Recycled Hydra\n");

}