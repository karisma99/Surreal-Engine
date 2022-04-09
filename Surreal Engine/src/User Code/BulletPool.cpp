
#include "BulletPool.h"
#include "Bullet.h"

BulletPool::BulletPool()
{

}

BulletPool::~BulletPool()
{
	DebugMsg::out("Deleting Bullets\n");

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

Bullet* BulletPool::GetBullet()
{
	Bullet* b;

	if (recycledItems.empty())
	{
		DebugMsg::out("New Bullet\n");
		b = new Bullet();
	}
	else
	{
		DebugMsg::out("Recycled Bullet\n");

		b = recycledItems.top();
		recycledItems.pop();
	}

	activeItems.push(b);
	return b;
}

void BulletPool::ReturnBullet(Bullet* b)
{
	activeItems.pop();

	recycledItems.push(static_cast<Bullet*>(b));
	DebugMsg::out("Recycled Bullet\n");

}