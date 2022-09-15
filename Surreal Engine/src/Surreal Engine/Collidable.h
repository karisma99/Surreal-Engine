#ifndef _Collidable
#define _Collidable

#include "RegistrationState.h"
#include "CollidableManager.h"
#include "SceneAttorney.h"
#include "CollisionVolume.h"


class CollidableManager;
class CollisionRegistrationCommand;
class CollisionDeregistrationCommand;
class CollisionVolume;
class CollisionVolumeBSphere;

class Collidable
{
	friend class CollidableAttorney;
public:
	enum VolumeType 
	{
		BSPHERE,
		AABB,
		OBB
	};

public:
	Collidable();
	Collidable(const Collidable& c) = delete;
	Collidable& operator = (const Collidable& t) = delete;
	virtual ~Collidable();

	virtual void CollisionTerrain() { };

	void SubmitCollisionRegistration();
	void SubmitCollisionDeregistration();
	const CollisionVolume& GetCollisionVolume();
	const CollisionVolumeBSphere& GetDefaultVolume();

private:
	void SceneRegistration();
	void SceneDegregistration();

	RegistrationState CurrState;
	CollidableGroup::CollidableCollectionRef pMyDeleteRef;
	CollidableManager::STypeID myID; 
	CollisionRegistrationCommand* pRegisterCmd;
	CollisionDeregistrationCommand* pDeregisterCmd;

	Model* pModel; 
	CollisionVolume* ColVolume; 
	CollisionVolumeBSphere* DefaultBSphere;

protected:
	template<typename C>
	void SetCollidableGroup()
	{
		myID = SceneAttorney::CollidableReg::GetCollisionMgr()->GetTypeID<C>();
	}

	void UpdateCollisionData(const Matrix& mat);
	void SetColliderModel(Model* const mod, VolumeType vol);

};

#endif _Collidable