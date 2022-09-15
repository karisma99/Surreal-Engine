
#include "VisualizerCommandPool.h"
#include "VisualizerCommand.h"

VisualizerCommandPool::VisualizerCommandPool()
{

}

VisualizerCommandPool::~VisualizerCommandPool()
{
	Trace::out("Deleting Commands\n");

	while (!createdItems.empty())
	{
		delete createdItems.front();
		createdItems.pop();
	}
}

VisualizerCommand* VisualizerCommandPool::GetCommand(Matrix m, Vect v, Collidable::VolumeType vol)
{
	VisualizerCommand* b;

	if (recycledItems.empty())
	{
		Trace::out("New Command\n");
		b = new VisualizerCommand(m, v, vol);
		createdItems.push(b);
	}
	else
	{
		Trace::out("Recycled Command\n");

		b = recycledItems.top();
		recycledItems.pop();
	}

	return b;
}

void VisualizerCommandPool::ReturnCommand(VisualizerCommand* b)
{
	recycledItems.push(static_cast<VisualizerCommand*>(b));
	Trace::out("Recycled Command\n");
}