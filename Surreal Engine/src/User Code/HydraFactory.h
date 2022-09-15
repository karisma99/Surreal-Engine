// HydraFactory

#ifndef _HydraFactory
#define _HydraFactory

#include "Matrix.h"
#include "HydraPool.h"

class GameObject;

class HydraFactory
{
private:
	static HydraFactory* ptrInstance;

	HydraFactory();
	HydraFactory(const HydraFactory&) = delete;
	HydraFactory& operator=(const HydraFactory&) = delete;
	~HydraFactory() = default;

	static HydraFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new HydraFactory();
		return *ptrInstance;
	};

	HydraPool myHydraPool;  // Back to be a non-static member instance

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time 
	void privCreateHydra(Matrix pos);
	void privRecycleHydra(GameObject* b);

public:

	// Static Methods
	static void CreateHydra(Matrix pos) { Instance().privCreateHydra(pos); };
	static void RecycleHydra(GameObject* b) { Instance().privRecycleHydra(b); };

	static void Terminate();

};


#endif _HydraFactory