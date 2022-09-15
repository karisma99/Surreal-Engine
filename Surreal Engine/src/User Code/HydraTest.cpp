// SpaceFrigate 

#include "HydraTest.h"
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
#include "Surreal Engine/Colors.h"

HydraTest::HydraTest()
{
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureFlat(ModelManager::Get("Hydra"), TextureManager::Get("HydraColor"));

	pGObj_SpaceshipBSphere = new GraphicsObject_ColorFlat(ModelManager::Get("Sphere"), Color::Blue);

	// Spaceship
	ShipScale.set(SCALE, 5.0f, 15.0f, 5.0f);
	ShipRotTrans = Matrix(ROT_Y, 90) * Matrix(TRANS, 20, 20, 0);

	// Creating matrices for in-world placement
	Matrix world;
	world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);

	CamShipOffset.set(0, 50, -150);
	CamLookAt.set(0, 10, 100);

	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	//Alarmable::SubmitAlarmRegistration(0, 5.0f);

	Collidable::SetCollidableGroup<HydraTest>();
	Collidable::SubmitCollisionRegistration();
	this->SetColliderModel(this->pGObj_SpaceFrigateLight->GetModel(), AABB);
}

HydraTest::~HydraTest()
{
	delete pGObj_SpaceFrigateLight;
	pGObj_SpaceFrigateLight = nullptr;

	delete pGObj_SpaceshipBSphere;
	pGObj_SpaceshipBSphere = nullptr;
}

void HydraTest::Update()
{
	// Spaceship adjust matrix

	Matrix world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);
	this->UpdateCollisionData(world);

	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_SpaceFrigateLight->GetModel()->GetRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_SpaceFrigateLight->GetModel()->GetCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	//pGObj_SpaceshipBSphere->SetWorld(worldBS);

	// Toggle the bounding sphere's visibility
	if (Keyboard::GetKeyInputState(SURREAL_KEY::SPACE_KEY))
	{
		BsphereToggle = true;
		//DebugMsg::out("Bounding sphere: On\n");
	}
	else
	{
		BsphereToggle = false;
		//DebugMsg::out("Bounding sphere: Off\n");
	}

	

}

void HydraTest::Draw()
{
	pGObj_SpaceFrigateLight->Render();
	if (BsphereToggle)
	{
		pGObj_SpaceshipBSphere->Render();
	}
}

void HydraTest::Collision(SpaceFrigate* sf)
{
	sf;
	Trace::out("Hydra Collide Frigate\n");
}

void HydraTest::Alarm0()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::AlarmID::Alarm0, 5.0f);
}

void HydraTest::Alarm1()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::AlarmID::Alarm1, 5.0f);
}

void HydraTest::SetCamera(Camera* c)
{
	this->pCam = c;
}
