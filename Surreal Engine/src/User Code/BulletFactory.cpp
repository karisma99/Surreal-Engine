// BulletFactory

#include "BulletFactory.h"
#include "BulletPool.h"
#include "Bullet.h"

BulletFactory* BulletFactory::ptrInstance = nullptr;

BulletFactory::BulletFactory()
{

}

void BulletFactory::privCreateBullet(Matrix pos)
{
	Bullet* b = myBulletPool.GetBullet();
	
	b->Initialize(pos);
}

void BulletFactory::privRecycleBullet(GameObject* b)
{
	myBulletPool.ReturnBullet(static_cast<Bullet*>(b));
}

void BulletFactory::Terminate()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


