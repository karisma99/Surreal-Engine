// SpaceFrigate 

#include "SpaceFrigate.h"
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
#include "BulletFactory.h"
#include "Surreal Engine/Visualizer.h"
#include "Surreal Engine/Colors.h"

SpaceFrigate::SpaceFrigate()
{
	pGObj_SpaceFrigateLight = new GraphicsObject_TextureFlat(ModelManager::Get("SpaceFrigate"), TextureManager::Get("SpaceFrigate"));

	pGObj_SpaceshipBSphere = new GraphicsObject_ColorFlat(ModelManager::Get("Sphere"), Color::Blue);

	// Spaceship
	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRotTrans = Matrix(ROT_Y, 90) * Matrix(TRANS, -40, 20, 0);

	// Creating matrices for in-world placement
	Matrix world;
	world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);

	CamShipOffset.set(0, -50, -150);
	CamLookAt.set(0, 10, 100);

	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(SURREAL_KEY::F_KEY, EventType::KEY_PRESS);
	//Alarmable::SubmitAlarmRegistration(0, 5.0f);

	Collidable::SetCollidableGroup<SpaceFrigate>(); 
	Collidable::SubmitCollisionRegistration();
	this->SetColliderModel(pGObj_SpaceFrigateLight->GetModel(), OBB);
}

SpaceFrigate::~SpaceFrigate()
{
	delete pGObj_SpaceFrigateLight;
	pGObj_SpaceFrigateLight = nullptr;

	delete pGObj_SpaceshipBSphere;
	pGObj_SpaceshipBSphere = nullptr;
}

void SpaceFrigate::Update()
{
	// Ship control. See also GAM 325/Week3 here: http://facweb.cs.depaul.edu/andre/GAM325/lecturenotes.html
	// Ship Rotation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyInputState(SURREAL_KEY::J_KEY))
	{
		ShipRotTrans = Matrix(ROT_Y, ShipRotAng) * ShipRotTrans;
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::L_KEY))
	{
		ShipRotTrans = Matrix(ROT_Y, -ShipRotAng) * ShipRotTrans;
	}

	// Ship translation movement (not using time-based values for simplicity)
	if (Keyboard::GetKeyInputState(SURREAL_KEY::I_KEY))
	{
		ShipRotTrans = Matrix(TRANS, Vect(0, 0, ShipTransSpeed)) * ShipRotTrans;
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::K_KEY))
	{
		ShipRotTrans = Matrix(TRANS, Vect(0, 0, -ShipTransSpeed)) * ShipRotTrans;
	}

	// Spaceship adjust matrix

	Matrix world = ShipScale * ShipRotTrans;
	pGObj_SpaceFrigateLight->SetWorld(world);
	this->UpdateCollisionData(world);

	
	// Placing the camera relative to the spaceship
	Vect vNewCamPos = CamLookAt * ShipRotTrans;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = CamShipOffset * ShipRotTrans;   // This moves the look-at point relative to ship's position and rotation
	pCam->SetOrientAndPosition( Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	pCam->UpdateCamera();
	

	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_SpaceFrigateLight->GetModel()->GetRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_SpaceFrigateLight->GetModel()->GetCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	pGObj_SpaceshipBSphere->SetWorld(worldBS);

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

void SpaceFrigate::Draw()
{
	pGObj_SpaceFrigateLight->Render();
	if (BsphereToggle)
	{
		pGObj_SpaceshipBSphere->RenderWireframe();
	}
}

void SpaceFrigate::Collision(SpaceFrigate* sf)
{
	sf;
	Trace::out("Frigate Collide Frigate\n");
}

void SpaceFrigate::Collision(HydraTest* sf)
{
	sf;
	Trace::out("Frigate Collide Hydra\n");
}

void SpaceFrigate::KeyPressed(SURREAL_KEY k)
{
	//Shooting
	if (k == SURREAL_KEY::F_KEY)
	{
		Trace::out("Pew Pew\n");
		BulletFactory::CreateBullet(ShipRotTrans); 
	}
}

void SpaceFrigate::Alarm0()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::AlarmID::Alarm0, 5.0f);
}

void SpaceFrigate::Alarm1()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();

	Alarmable::SubmitAlarmRegistration(AlarmableManager::AlarmID::Alarm1, 5.0f);
}

void SpaceFrigate::SetCamera(Camera* c)
{
	this->pCam = c;
}
