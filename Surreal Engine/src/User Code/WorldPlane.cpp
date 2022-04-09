// Plane 

#include "WorldPlane.h"
#include "AzulCore.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Inputable.h"
#include "../Surreal Engine/EventType.h"
#include "../Surreal Engine/SceneManager.h"
#include "../User Code/SceneOne.h"

WorldPlane::WorldPlane()
{
	pGObj_Plane = new GraphicsObject_TextureFlat(ModelManager::Get("Plane"), ShaderManager::Get("Flat"), TextureManager::Get("Grid"));
	pGObj_Axis = new GraphicsObject_ColorNoTexture(ModelManager::Get("Axis"), ShaderManager::Get("ColorNoTex"));

	// Creating matrices for in-world placement
	Matrix world;
	world = Matrix(IDENTITY);
	pGObj_Axis->SetWorld(world);
	world = Matrix(SCALE, 400, 400, 400);
	pGObj_Plane->SetWorld(world);

	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EventType::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_M, EventType::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_1, EventType::KEY_PRESS);
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
	pGObj_Plane->Render(pCam);
	pGObj_Axis->Render(pCam);
}

void WorldPlane::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		DebugMsg::out("SPACE pressed\n"); 
		break; 
	case AZUL_KEY::KEY_M:
		DebugMsg::out("M pressed\n");
		break;
	case AZUL_KEY::KEY_1:
		DebugMsg::out("1 pressed\n");
		SceneManager::SetNextScene(new SceneOne());
		break;
	default:
		DebugMsg::out("ERROR: Key %i unproccesed\n", k); 
	}
}

void WorldPlane::KeyReleased(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		DebugMsg::out("SPACE Released\n");
		break;
	case AZUL_KEY::KEY_M:
		DebugMsg::out("M Released\n");
		break;
	default:
		DebugMsg::out("ERROR: Key %i unproccesed\n", k);
	}
}

void WorldPlane::SetCamera(Camera* c)
{
	this->pCam = c;
}