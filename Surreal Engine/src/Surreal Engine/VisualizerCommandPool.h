// VisualizerCommandPool

#ifndef _VisualizerCommandPool
#define _VisualizerCommandPool

#include <stack>
#include <queue>
#include "Collidable.h"

class VisualizerCommand;

class VisualizerCommandPool
{
private:
	std::stack<VisualizerCommand*> recycledItems;
	std::queue<VisualizerCommand*> createdItems;

public:
	VisualizerCommandPool();
	VisualizerCommandPool(const VisualizerCommandPool&) = delete;
	VisualizerCommandPool& operator=(const VisualizerCommandPool&) = delete;
	~VisualizerCommandPool();

	VisualizerCommand* GetCommand(Matrix m, Vect v, Collidable::VolumeType vol);

	void ReturnCommand(VisualizerCommand* b);
};


#endif _VisualizerCommandPool
