
#include "BubblePool.h"
#include "Bubble.h"

BubblePool::BubblePool()
{

}

BubblePool::~BubblePool()
{
	Trace::out("Deleting Bubbles\n");

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

Bubble* BubblePool::GetBubble()
{
	Bubble* b;

	if (recycledItems.empty())
	{
		Trace::out("New Bubble\n");
		b = new Bubble();
	}
	else
	{
		Trace::out("Recycled Bubble\n");

		b = recycledItems.top();
		recycledItems.pop();
	}

	activeItems.push(b);
	return b;
}

void BubblePool::ReturnBubble(Bubble* b)
{
	activeItems.pop();

	recycledItems.push(static_cast<Bubble*>(b));
	Trace::out("Recycled Bubble\n");

}