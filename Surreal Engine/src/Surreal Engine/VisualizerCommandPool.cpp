
#include "VisualizerCommandPool.h"
#include "VisualizerCommand.h"

VisualizerCommandPool::VisualizerCommandPool()
{

}

VisualizerCommandPool::~VisualizerCommandPool()
{
	DebugMsg::out("Deleting Bullets\n");

	while (!activeItems.empty())
	{
		delete activeItems.front();
		activeItems.pop();
	}

	while (!recycledItems.empty())
	{
		delete recycledItems.top();
		recycledItems.pop();
	}
}

VisualizerCommand* VisualizerCommandPool::GetCommand(Matrix m, Vect v)
{
	VisualizerCommand* b;

	if (recycledItems.empty())
	{
		DebugMsg::out("New Command\n");
		b = new VisualizerCommand(m, v);
	}
	else
	{
		DebugMsg::out("Recycled Command\n");

		b = recycledItems.top();
		recycledItems.pop();
	}

	activeItems.push(b);
	return b;
}

void VisualizerCommandPool::ReturnCommand(VisualizerCommand* b)
{
	activeItems.pop();

	recycledItems.push(static_cast<VisualizerCommand*>(b));
	DebugMsg::out("Recycled Command\n");

}