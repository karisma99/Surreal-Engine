// Plane 

#include "World.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/SceneManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Inputable.h"
#include "../Surreal Engine/EventType.h"
#include "../User Code/SceneDemo.h"
#include "../User Code/HydraManager.h"
#include "Surreal Graphics/Model.h"
#include "Surreal Graphics/Skybox.h"

World::World()
{
	this->CreateSkybox(500);

	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(SURREAL_KEY::SPACE_KEY, EventType::KEY_PRESS);
	Inputable::SubmitKeyRegistration(SURREAL_KEY::M_KEY, EventType::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(SURREAL_KEY::NUM_2_KEY, EventType::KEY_PRESS);
}

World::~World()
{
	delete pGObj_Skybox;
	pGObj_Skybox = nullptr;

	delete pSkybox;
	pSkybox = nullptr;
}

void World::Update()
{
	HydraManager::SpawnHydra();
}

void World::Draw()
{
	pGObj_Skybox->Render();
}

void World::KeyPressed(SURREAL_KEY k)
{
	switch (k)
	{
	case SURREAL_KEY::SPACE_KEY:
		Trace::out("SPACE pressed\n");
		break;
	case SURREAL_KEY::M_KEY:
		Trace::out("M pressed\n");
		break;
	case SURREAL_KEY::NUM_2_KEY:
		Trace::out("2 pressed\n");
		SceneManager::SetNextScene(new SceneDemo());
		break;
	default:
		Trace::out("ERROR: Key %i unproccesed\n", k);
	}
}

void World::KeyReleased(SURREAL_KEY k)
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

void World::CreateSkybox(float scale)
{
	pSkybox = new Skybox(scale);
	pGObj_Skybox = new GraphicsObject_TextureFlat(pSkybox->GetModel(), TextureManager::Get("skybox"));

	// adjust matrix
	Matrix world = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 0) * Matrix(TRANS, 0, -450, 0);
	pGObj_Skybox->SetWorld(world);
}