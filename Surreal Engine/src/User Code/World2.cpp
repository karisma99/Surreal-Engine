// World2 

#include "World2.h"
#include "AzulCore.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/SceneManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Inputable.h"
#include "../Surreal Engine/EventType.h"
#include "../User Code/SceneDemo.h"
#include "../User Code/FoodManager.h"
#include "GpuVertTypes.h"
#include "Model.h"

World2::World2()
{
	this->CreateSkybox(500);

	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_SPACE, EventType::KEY_PRESS);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_M, EventType::KEY_RELEASE);
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_2, EventType::KEY_PRESS);
}

World2::~World2()
{
	delete pGObj_Skybox;
	pGObj_Skybox = nullptr;

	delete pSkyboxModel;
}

void World2::Update()
{

	FoodManager::SpawnFood();

}

void World2::Draw()
{
	pGObj_Skybox->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void World2::KeyPressed(AZUL_KEY k)
{
	switch (k)
	{
	case AZUL_KEY::KEY_SPACE:
		DebugMsg::out("SPACE pressed\n");
		break;
	case AZUL_KEY::KEY_M:
		DebugMsg::out("M pressed\n");
		break;
	case AZUL_KEY::KEY_2:
		DebugMsg::out("2 pressed\n");
		SceneManager::SetNextScene(new SceneDemo());
		break;
	default:
		DebugMsg::out("ERROR: Key %i unproccesed\n", k);
	}
}

void World2::KeyReleased(AZUL_KEY k)
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

void World2::CreateSkybox(float scale)
{
	// creating model
	int nverts = 24;
	VertexStride_VUN* pVerts = new VertexStride_VUN[nverts];

	int ntri = 12;
	TriangleIndex* pTriList = new TriangleIndex[ntri];

	// Setting up faces
		// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(scale, scale, scale, 0.5f, 0.333f, 0, 0, 0);
	pVerts[vind + 1].set(-scale, scale, scale, 0.75f, 0.333f, 0, 0, 0);
	pVerts[vind + 2].set(-scale, -scale, scale, 0.75f, 0.667f, 0, 0, 0);
	pVerts[vind + 3].set(scale, -scale, scale, 0.5f, 0.65f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, 0.25f, 0.333f, 0, 0, 0);
	pVerts[vind + 1].set(-scale, scale, -scale, 0.0f, 0.333f, 0, 0, 0);
	pVerts[vind + 2].set(-scale, -scale, -scale, 0, 0.66f, 0, 0, 0);
	pVerts[vind + 3].set(scale, -scale, -scale, 0.25f, 0.66f, 0, 0, 0);
	pTriList[tind].set(vind + 0, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind + 0, vind + 2, vind + 3);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, 0.25f, 0.333f, 0, 0, 0);
	pVerts[vind + 1].set(scale, scale, scale, 0.5f, 0.333f, 0, 0, 0);
	pVerts[vind + 2].set(scale, -scale, scale, 0.5f, 0.65f, 0, 0, 0);
	pVerts[vind + 3].set(scale, -scale, -scale, 0.25f, 0.66f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-scale, scale, scale, 0.75f, 0.335f, 0, 0, 0);
	pVerts[vind + 1].set(-scale, scale, -scale, 1.0f, 0.335f, 0, 0, 0);
	pVerts[vind + 2].set(-scale, -scale, -scale, 1.0f, 0.665f, 0, 0, 0);
	pVerts[vind + 3].set(-scale, -scale, scale, 0.75f, 0.665f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, scale, -scale, 0.5f, 0.0, 0, 0, 0);
	pVerts[vind + 1].set(-scale, scale, -scale, 0.75f, 0.0, 0, 0, 0);
	pVerts[vind + 2].set(-scale, scale, scale, 0.75f, 0.333f, 0, 0, 0);
	pVerts[vind + 3].set(scale, scale, scale, 0.5f, 0.333f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(scale, -scale, scale, 0.5f, 0.6667f, 0, 0, 0);
	pVerts[vind + 1].set(-scale, -scale, scale, 0.72f, 0.666f, 0, 0, 0);
	pVerts[vind + 2].set(-scale, -scale, -scale, 0.72f, 0.99f, 0, 0, 0);
	pVerts[vind + 3].set(scale, -scale, -scale, 0.5f, 0.99f, 0, 0, 0);
	pTriList[tind].set(vind + 2, vind + 1, vind + 0);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind + 0);

	pSkyboxModel = new Model(pVerts, nverts, pTriList, ntri);

	delete[] pVerts;
	delete[] pTriList;

	// graphics
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_Skybox = new GraphicsObject_TextureFlat(pSkyboxModel, ShaderManager::Get("Flat"), TextureManager::Get("heaven"));

	// adjust matrix
	Matrix world = Matrix(SCALE, 1, 1, 1) * Matrix(ROT_Y, 0) * Matrix(TRANS, 0, 200, 0);
	pGObj_Skybox->SetWorld(world);
}