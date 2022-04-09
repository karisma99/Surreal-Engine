// BulletPool

#ifndef _BulletPool
#define _BulletPool

#include <stack>
#include <queue>
class Bullet;

class BulletPool
{
private:
	std::stack<Bullet*> recycledItems;
	std::queue<Bullet*> activeItems;

public:
	BulletPool();
	BulletPool(const BulletPool&) = delete;
	BulletPool& operator=(const BulletPool&) = delete;
	~BulletPool();

	Bullet* GetBullet();

	void ReturnBullet(Bullet* b);
};


#endif _BulletPool
