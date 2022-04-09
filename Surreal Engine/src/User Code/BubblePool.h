// BubblePool

#ifndef _BubblePool
#define _BubblePool

#include <stack>
#include <queue>
class Bubble;

class BubblePool
{
private:
	std::stack<Bubble*> recycledItems;
	std::queue<Bubble*> activeItems;

public:
	BubblePool();
	BubblePool(const BubblePool&) = delete;
	BubblePool& operator=(const BubblePool&) = delete;
	~BubblePool();

	Bubble* GetBubble();

	void ReturnBubble(Bubble* b);
};


#endif _BubblePool
