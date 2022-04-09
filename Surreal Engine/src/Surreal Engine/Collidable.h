#ifndef _Collidable
#define _Collidable

#include "RegistrationState.h"
#include "CollidableManager.h"
#include "SceneAttorney.h"
#include "CollisionVolumeBSphere.h"

class CollidableManager;
class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;

class Collidable
{
	friend class CollidableAttorney;

public:
	Collidable();
	Collidable(const Collidable& c) = delete;
	Collidable& operator = (const Collidable& t) = delete;
	virtual ~Collidable();

	void SubmitCollisionRegistration();
	void SubmitCollisionDeregistration();
	const CollisionVolumeBSphere& GetBSphere();

private:
	void SceneRegistration();
	void SceneDegregistration();

	RegistrationState CurrState;
	CollidableGroup::CollidableCollectionRef pMyDeleteRef;
	CollidableManager::STypeID myID; 
	CollisionRegistrationCommand* pRegisterCmd;
	CollisionDeregistrationCommand* pDeregisterCmd;

	Model* pModel; 
	CollisionVolumeBSphere BSphere;

protected:
	template<typename C>
	void SetCollidableGroup()
	{
		myID = SceneAttorney::CollidableReg::GetCollisionMgr()->GetTypeID<C>();
	}

	void UpdateCollisionData(const Matrix& mat);
	void SetColliderModel(Model* const mod);

};

#endif _Collidable