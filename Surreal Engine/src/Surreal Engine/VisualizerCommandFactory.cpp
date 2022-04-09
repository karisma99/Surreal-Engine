// VisualizerCommandFactory

#include "VisualizerCommandFactory.h"
#include "VisualizerCommandPool.h"
#include "VisualizerCommand.h"

VisualizerCommandFactory* VisualizerCommandFactory::ptrInstance = nullptr;

VisualizerCommandFactory::VisualizerCommandFactory()
{

}

VisualizerCommand* VisualizerCommandFactory::privCreateCommand(Matrix m, Vect v)
{
	VisualizerCommand* b = myCommandPool.GetCommand(m, v);

	b->Update(m, v);

	return b;
}

void VisualizerCommandFactory::privRecycleCommand(VisualizerCommand* cmd)
{
	myCommandPool.ReturnCommand(static_cast<VisualizerCommand*>(cmd));
}

void VisualizerCommandFactory::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


