#ifndef _CollisionTestCommandBase
#define _CollisionTestCommandBase

class CollisionTestCommandBase
{
public:
	CollisionTestCommandBase();
	CollisionTestCommandBase(const CollisionTestCommandBase& c) = delete;
	CollisionTestCommandBase& operator = (const CollisionTestCommandBase& t) = delete;
	virtual ~CollisionTestCommandBase();

	virtual void Execute();
private:

};

#endif _CollisionTestCommandBase
