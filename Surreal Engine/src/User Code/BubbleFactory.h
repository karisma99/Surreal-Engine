// BulletFactory

#ifndef _BubbleFactory
#define _BubbleFactory

#include "Matrix.h"
#include "BubblePool.h"

class GameObject;

class BubbleFactory
{
private:
	static BubbleFactory* ptrInstance;

	BubbleFactory();
	BubbleFactory(const BubbleFactory&) = delete;
	BubbleFactory& operator=(const BubbleFactory&) = delete;
	~BubbleFactory() = default;

	static BubbleFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new BubbleFactory();
		return *ptrInstance;
	};

	BubblePool myBubblePool;  // Back to be a non-static member instance

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time 
	void privCreateBubble(Matrix pos);
	void privRecycleBubble(GameObject* b);

public:

	// Static Methods
	static void CreateBubble(Matrix pos) { Instance().privCreateBubble(pos); };
	static void RecycleBubble(GameObject* b) { Instance().privRecycleBubble(b); };

	static void Terminate();

};


#endif _BubbleFactory