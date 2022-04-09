//SceneDemo

#include "SceneDemo.h"
#include "../User Code/WorldPlane.h"
#include "../User Code/SpaceFrigate.h"
#include "../User Code/BulletFactory.h"
#include "../Surreal Engine/Collidable.h"
#include "../User Code/HydraTest.h"
#include "../User Code/HudTest.h"

void SceneDemo::Initialize()
{
	pWorldPlane = new WorldPlane();
	pFrigate = new SpaceFrigate();
	//pFrigate2 = new SpaceFrigate();
	pHydra = new HydraTest();
	pHud = new HudTest();

	SetCollisionPair<SpaceFrigate, HydraTest>();
	SetCollisionSelf<SpaceFrigate>();

	SetCamera();
}

void SceneDemo::SceneEnd()
{

	BulletFactory::Terminate();

	delete pWorldPlane;
	pWorldPlane = nullptr;

	delete pHydra;
	pHydra = nullptr;

	delete pFrigate;
	pFrigate = nullptr;

	delete pHud;
	pHud = nullptr;

	//delete pFrigate2;
	//pFrigate2 = nullptr;

}

void SceneDemo::SetCamera()
{
	CameraManager* cm = this->GetCameraManager();
	pFrigate->SetCamera(cm->GetCurrentCamera());
	//pFrigate2->SetCamera(cm->GetCurrentCamera());
	pWorldPlane->SetCamera(cm->GetCurrentCamera());
	pHydra->SetCamera(cm->GetCurrentCamera());
}