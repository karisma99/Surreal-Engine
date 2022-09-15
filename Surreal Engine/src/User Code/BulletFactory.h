// BulletFactory

#ifndef _BulletFactory
#define _BulletFactory

#include "Matrix.h"
#include "BulletPool.h"

class GameObject;

class BulletFactory
{
private:
	static BulletFactory* ptrInstance;

	BulletFactory();
	BulletFactory(const BulletFactory&) = delete;
	BulletFactory& operator=(const BulletFactory&) = delete;
	~BulletFactory() = default;								

	static BulletFactory& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new BulletFactory();
		return *ptrInstance;
	};

	BulletPool myBulletPool;  // Back to be a non-static member instance

	// Note: Some factory designs also keep a list of 'currently active' objects
	// Often useful at cleanup time 
	void privCreateBullet(Matrix pos);
	void privRecycleBullet(GameObject* b);

public:

	// Static Methods
	static void CreateBullet(Matrix pos) { Instance().privCreateBullet(pos); };
	static void RecycleBullet(GameObject* b) { Instance().privRecycleBullet(b); };

	static void Terminate();

};


#endif _BulletFactory