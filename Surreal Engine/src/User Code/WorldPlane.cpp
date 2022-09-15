// Plane 

#include "WorldPlane.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Inputable.h"
#include "../Surreal Engine/EventType.h"
#include "../Surreal Engine/SceneManager.h"
#include "../User Code/SceneOne.h"
#include "Surreal Engine/Colors.h"

WorldPlane::WorldPlane()
{
	pGObj_Plane = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"), TextureManager::Get("Grid"));
	pGObj_Axis = new GraphicsObject_ColorFlat(ModelManager::Get("Axis"), Color::Blue);

	// Creating matrices for in-world placement
	Matrix world;
	world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);
	world = Matrix(SCALE, 400, 400, 400);
	pGObj_Plane->SetWorld(world);

	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(SURREAL_KEY::SPACE_KEY, EventType::KEY_PRESS);
	Inputable::SubmitKeyRegistration(SURREAL_KEY::M_KEY, EventType::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(SURREAL_KEY::NUM_1_KEY, EventType::KEY_PRESS);
}

WorldPlane::~WorldPlane()
{
	delete pGObj_Plane;
	pGObj_Plane = nullptr;

	delete pGObj_Axis;
	pGObj_Axis = nullptr;
}

void WorldPlane::Update()
{

}

void WorldPlane::Draw()
{
	pGObj_Plane->Render();
	pGObj_Axis->Render();
}

void WorldPlane::KeyPressed(SURREAL_KEY k)
{
	switch (k)
	{
	case SURREAL_KEY::SPACE_KEY:
		Trace::out("SPACE pressed\n"); 
		break; 
	case SURREAL_KEY::M_KEY:
		Trace::out("M pressed\n");
		break;
	case SURREAL_KEY::NUM_1_KEY:
		Trace::out("1 pressed\n");
		SceneManager::SetNextScene(new SceneOne());
		break;
	default:
		Trace::out("ERROR: Key %i unproccesed\n", k); 
	}
}

void WorldPlane::KeyReleased(SURREAL_KEY k)
{
	switch (k)
	{
	case SURREAL_KEY::SPACE_KEY:
		Trace::out("SPACE Released\n");
		break;
	case SURREAL_KEY::M_KEY:
		Trace::out("M Released\n");
		break;
	default:
		Trace::out("ERROR: Key %i unproccesed\n", k);
	}
}

void WorldPlane::SetCamera(Camera* c)
{
	this->pCam = c;
}