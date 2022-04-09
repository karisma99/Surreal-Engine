//Drawable

#include "Collidable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionderegistrationCommand.h"

Collidable::Collidable()
{
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
	pRegisterCmd = new CollisionRegistrationCommand(this);
	pDeregisterCmd = new CollisionDeregistrationCommand(this);
	pModel = nullptr;
	myID = -1;
}

Collidable::~Collidable()
{
	delete pRegisterCmd; 
	pRegisterCmd = nullptr; 

	delete pDeregisterCmd;
	pDeregisterCmd = nullptr;
}

void Collidable::SceneRegistration()
{
	assert(CurrState == RegistrationState::PENDING_REGISTRATION);
	SceneAttorney::CollidableReg::GetCollisionMgr()->GetColGroup(myID)->Register(this, pMyDeleteRef);
	CurrState = RegistrationState::CURRENTLY_REGISTERED;
}

void Collidable::SceneDegregistration()
{
	assert(CurrState == RegistrationState::PENDING_DEREGISTRATION);
	SceneAttorney::CollidableReg::GetCollisionMgr()->GetColGroup(myID)->Deregister(pMyDeleteRef);
	CurrState = RegistrationState::CURRENTLY_DEREGISTERED;
}

void Collidable::SubmitCollisionRegistration()
{
	assert(CurrState == RegistrationState::CURRENTLY_DEREGISTERED);
	SceneAttorney::CollidableReg::SubmittCommand(SceneManager::GetCurrentScene(), pRegisterCmd);
	CurrState = RegistrationState::PENDING_REGISTRATION;
}

const CollisionVolumeBSphere& Collidable::GetBSphere()
{
	return BSphere;
}

void Collidable::SubmitCollisionDeregistration()
{
	assert(CurrState == RegistrationState::CURRENTLY_REGISTERED);
	SceneAttorney::CollidableReg::SubmittCommand(SceneManager::GetCurrentScene(), pDeregisterCmd);
	CurrState = RegistrationState::PENDING_DEREGISTRATION;
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	BSphere.ComputeData(pModel, mat);
}

void Collidable::SetColliderModel(Model* const mod)
{
	pModel = mod;
}