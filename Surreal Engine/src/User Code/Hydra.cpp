// Hydra 

#include "Hydra.h"
#include "Surreal Engine/ModelManager.h"
#include "Surreal Engine/ShaderManager.h"
#include "Surreal Engine/TextureManager.h"
#include "Surreal Engine/CameraManager.h"
#include "Surreal Engine/Drawable.h"
#include "Surreal Engine/Updateable.h"
#include "Surreal Engine/Alarmable.h"
#include "Surreal Engine/Inputable.h"
#include "Surreal Engine/Collidable.h"
#include "Surreal Engine/SceneManager.h"
#include "User Code/Fish.h"
#include "User Code/HydraManager.h"
#include "User Code/HydraFactory.h"
#include "Surreal Engine/Colors.h"
#include "Surreal Engine/TimeManager.h"
#include "Surreal Engine/TerrainObject.h"

Hydra::Hydra()
{
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureFlat(ModelManager::Get("Hydra"), TextureManager::Get("HydraColor"));

	pGObj_SpaceshipBSphere = new GraphicsObject_ColorFlat(ModelManager::Get("Sphere"), Color::Blue);

	// Spaceship
	HydraScale.set(SCALE, 5.0f, 20.0f, 5.0f);
	HydraRotTrans = Matrix(ROT_Y, 90) * Matrix(TRANS, -70, 20, 50);

	// Creating matrices for in-world placement
	Matrix world;
	world = HydraScale * HydraRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);

	CamShipOffset.set(0, 50, -150);
	CamLookAt.set(0, 10, 100);

	Collidable::SetCollidableGroup<Hydra>();
	this->SetColliderModel(pGObj_SpaceFrigateLight->GetModel(), BSPHERE);
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
	HydraRotTrans = Matrix(TRANS, Vect(HydraSpeed * TimeManager::GetFrameTime(), 0, 0)) * HydraRotTrans;

	float offset = 70;
	Vect terrainCellCenter = SceneManager::GetCurrentScene()->GetTerrain()->GetCellCenterAtPosition(Vect(HydraRotTrans.M12(), HydraRotTrans.M13(), HydraRotTrans.M14()));

	Matrix world = HydraScale * HydraRotTrans * Matrix(TRANS, 0, terrainCellCenter.Y() - offset, 0);
	pGObj_SpaceFrigateLight->SetWorld(world);
	this->UpdateCollisionData(world);
}

void Hydra::Draw()
{
	pGObj_SpaceFrigateLight->Render();
}

void Hydra::Collision(Fish* sf)
{
	sf;
	Trace::out("Hydra Collide Fish\n");
	Destroy();
}

void Hydra::Collision(Bubble* sf)
{
	sf;
	Trace::out("Hydra Collide Bubble\n");
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
