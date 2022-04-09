// Hydra 

#include "Hydra.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Updateable.h"
#include "../Surreal Engine/Alarmable.h"
#include "../Surreal Engine/Inputable.h"
#include "../Surreal Engine/Collidable.h"
#include "../Surreal Engine/SceneManager.h"
#include "../User Code/Fish.h"
#include "../User Code/HydraManager.h"
#include "../User Code/HydraFactory.h"

Hydra::Hydra()
{
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureLight(ModelManager::Get("Hydra"), ShaderManager::Get("Light"), TextureManager::Get("HydraColor"), LightColor, LightPos);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_SpaceshipBSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ConstantColor"), Blue);

	// Spaceship
	HydraScale.set(SCALE, 5.0f, 20.0f, 5.0f);
	HydraRotTrans = Matrix(ROT_Y, 90) * Matrix(TRANS, -70, 20, 50);

	// Creating matrices for in-world placement
	Matrix world;
	world = HydraScale * HydraRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);

	CamShipOffset.set(0, 50, -150);
	CamLookAt.set(0, 10, 100);

	this->SetColliderModel(pGObj_SpaceFrigateLight->getModel());
	Collidable::SetCollidableGroup<Hydra>();
}

Hydra::~Hydra()
{
	delete pGObj_SpaceFrigateLight;
	pGObj_SpaceFrigateLight = nullptr;

	delete pGObj_SpaceshipBSphere;
	pGObj_SpaceshipBSphere = nullptr;
}

void Hydra::Initialize(Matrix m)
{
	this->SubmitEntry();
	HydraRotTrans = m;
	FacePlayer();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm0, 3.0f);
}

void Hydra::Update()
{
	HydraRotTrans = Matrix(TRANS, Vect(HydraSpeed, 0, 0)) * HydraRotTrans;
	Matrix world = HydraScale * HydraRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);
	this->UpdateCollisionData(world);
}

void Hydra::Draw()
{
	pGObj_SpaceFrigateLight->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void Hydra::Collision(Fish* sf)
{
	sf;
	DebugMsg::out("Hydra Collide Fish\n");
	Destroy();
}

void Hydra::Collision(Bubble* sf)
{
	sf;
	DebugMsg::out("Hydra Collide Bubble\n");
	Destroy();
}

void Hydra::Alarm0()
{
	FacePlayer();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::AlarmID::Alarm0, 3.0f);
}

void Hydra::Destroy()
{
	this->SubmitExit();
}

void Hydra::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
}

void Hydra::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::Alarm0);
	HydraManager::ReturnHydra();
	HydraFactory::RecycleHydra(this);
}

void Hydra::FacePlayer()
{
	Vect fishPosition = HydraManager::GetPlayerPosition().get(ROW_3);
	Vect myPos = HydraRotTrans.get(ROW_3);
	Vect direction = (fishPosition - myPos).norm();

	float dot = HydraRotTrans.get(ROW_0).dot(direction);
	float angle = acos(dot);

	Vect cross = HydraRotTrans.get(ROW_0).cross(direction);
	if (cross.Y() < 0)
		angle *= -1;

	HydraRotTrans = Matrix(ROT_Y, angle) * HydraRotTrans;

}
