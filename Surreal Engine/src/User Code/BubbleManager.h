// BubbleManager

#ifndef _BubbleManager
#define _BubbleManager

#include "Matrix.h"

class SurrealSprite;

class BubbleManager
{
	friend class SceneOne;
	friend class SceneTwo;
private:
	static BubbleManager* ptrInstance;

	BubbleManager();
	BubbleManager(const BubbleManager& c) = delete;
	BubbleManager& operator = (const BubbleManager& t) = delete;
	~BubbleManager() = default;

	static BubbleManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new BubbleManager;
		return *ptrInstance;
	};

public:
	static void ShootBubble(Matrix pos) { Instance().privShootBubble(pos); };
	static int GetBubbleCount() { return Instance().privGetBubbleCount(); };
	static void ReturnBubble() { Instance().privReturnBubble(); };

private:

	void privDelete();
	static void Delete() { Instance().privDelete(); };

	void privShootBubble(Matrix pos);
	int privGetBubbleCount();
	void privReturnBubble();

	static Vect DEFAULT_COLOR;
	int liveBubbles;
	int maxBubbles = 3;

};

#endif _BubbleManager