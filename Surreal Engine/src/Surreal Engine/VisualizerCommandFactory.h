// VisualizerCommandFactory

#ifndef _VisualizerCommandFactory
#define _VisualizerCommandFactory

#include "AzulCore.h"
#include "VisualizerCommandPool.h"

class VisualizerCommand; 
class VisualizerCommandPool;

class VisualizerCommandFactory
{
private:
	static VisualizerCommandFactory* ptrInstance;

	VisualizerCommandFactory();
	VisualizerCommandFactory(const VisualizerCommandFactory&) = delete;
	VisualizerCommandFactory& operator=(const VisualizerCommandFactory&) = delete;
	~VisualizerCommandFactory() = default;

	static VisualizerCommandFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new VisualizerCommandFactory();
		return *ptrInstance;
	};

	VisualizerCommandPool myCommandPool;  // Back to be a non-static member instance

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time 
	VisualizerCommand* privCreateCommand(Matrix m, Vect v);
	void privRecycleCommand(VisualizerCommand* cmd);
	void privDelete();

public:

	// Static Methods
	static VisualizerCommand* CreateCommand(Matrix m, Vect v) { return Instance().privCreateCommand(m, v); };
	static void RecycleCommand(VisualizerCommand* cmd) { Instance().privRecycleCommand(cmd); };

	static void Delete() { Instance().privDelete(); }

};


#endif _VisualizerCommandFactory