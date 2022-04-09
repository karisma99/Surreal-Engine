// VisualizerCommandPool

#ifndef _VisualizerCommandPool
#define _VisualizerCommandPool

#include "AzulCore.h"
#include <stack>
#include <queue>
class VisualizerCommand;

class VisualizerCommandPool
{
private:
	std::stack<VisualizerCommand*> recycledItems;
	std::queue<VisualizerCommand*> activeItems;

public:
	VisualizerCommandPool();
	VisualizerCommandPool(const VisualizerCommandPool&) = delete;
	VisualizerCommandPool& operator=(const VisualizerCommandPool&) = delete;
	~VisualizerCommandPool();

	VisualizerCommand* GetCommand(Matrix m, Vect v);

	void ReturnCommand(VisualizerCommand* b);
};


#endif _VisualizerCommandPool
