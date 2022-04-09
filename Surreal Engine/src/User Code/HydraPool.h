// HydraPool

#ifndef _HydraPool
#define _HydraPool

#include <stack>
#include <queue>
class Hydra;

class HydraPool
{
private:
	std::stack<Hydra*> recycledItems;
	std::queue<Hydra*> createdItems;

public:
	HydraPool();
	HydraPool(const HydraPool&) = delete;
	HydraPool& operator=(const HydraPool&) = delete;
	~HydraPool();

	Hydra* GetHydra();

	void ReturnHydra(Hydra* b);
};


#endif _HydraPool
