// BulletFactory

#include "BubbleFactory.h"
#include "BubblePool.h"
#include "Bubble.h"
#include "BubbleManager.h"

BubbleFactory* BubbleFactory::ptrInstance = nullptr;

BubbleFactory::BubbleFactory()
{

}

void BubbleFactory::privCreateBubble(Matrix pos)
{
	Bubble* b = myBubblePool.GetBubble();
	
	b->Initialize(pos);
}

void BubbleFactory::privRecycleBubble(GameObject* b)
{
	myBubblePool.ReturnBubble(static_cast<Bubble*>(b));
	BubbleManager::ReturnBubble();
}

void BubbleFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


