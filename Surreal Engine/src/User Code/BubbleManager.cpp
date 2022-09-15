//BubbleManager

#include "BubbleManager.h"
#include "BubbleFactory.h"
#include "../Surreal Engine/SurrealSprite.h"

BubbleManager* BubbleManager::ptrInstance = nullptr;

BubbleManager::BubbleManager()
{
	liveBubbles = 0;
}

void BubbleManager::privDelete()
{
	BubbleFactory::Terminate();

	delete ptrInstance;
	ptrInstance = nullptr;
}

void BubbleManager::privShootBubble(Matrix pos)
{
	if (liveBubbles < 3)
	{
		BubbleFactory::CreateBubble(pos);
		liveBubbles++;
	}
}

int BubbleManager::privGetBubbleCount()
{
	return maxBubbles - liveBubbles;
}

void BubbleManager::privReturnBubble()
{
	liveBubbles--;
}


