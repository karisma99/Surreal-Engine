// SpaceFrigate 

#include "Fish.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Updateable.h"
#include "../Surreal Engine/Alarmable.h"
#include "../Surreal Engine/SceneManager.h"
#include "../User Code/BubbleManager.h"
#include "../User Code/FishManager.h"

Fish::Fish()
{
	// Light
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	pGObj_FishLight = new GraphicsObject_TextureLight(ModelManager::Get("Fish"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_FishBSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ConstantColor"), Blue);

	// Spaceship
	FishScale.set(SCALE, 30.0f, 7.0f, 10.0f);
	FishRotTrans = Matrix(ROT_Y, 135) * Matrix(TRANS, 0, 20, 0);

	// Creating matrices for in-world placement
	Matrix world;
	world = FishScale * FishRotTrans;
	pGObj_FishLight->SetWorld(world);

	CamShipOffset.set(-300, 100, 0);
	CamLookAt.set(0, 10, 0);

	SetModels(); 
	modelRef = modelCol.begin();
	moving = false;
	forward = true;
	
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(AZUL_KEY::KEY_F, EventType::KEY_PRESS);
	//Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm0, 3.0f);

	Collidable::SetCollidableGroup<Fish>(); 
	Collidable::SubmitCollisionRegistration(); 
	this->SetColliderModel(pGObj_FishLight->getModel());
}

Fish::~Fish()
{
	delete pGObj_FishLight;
	pGObj_FishLight = nullptr;

	delete pGObj_FishBSphere;
	pGObj_FishBSphere = nullptr;

	for (auto& it : modelCol)
	{
		delete it; 
		it = nullptr;
	}
}

void Fish::Update()
{
	moving = false;
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_J))
	{
		FishRotTrans = Matrix(ROT_Y, FishRotAng) * FishRotTrans;
		moving = true;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_L))
	{
		FishRotTrans = Matrix(ROT_Y, -FishRotAng) * FishRotTrans;
		moving = true;
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_I))
	{
		FishRotTrans = Matrix(TRANS, Vect(FishTransSpeed, 0, 0)) * FishRotTrans;
		moving = true;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_K))
	{
		FishRotTrans = Matrix(TRANS, Vect(-FishTransSpeed, 0, 0)) * FishRotTrans;
		moving = true;
	}

	// Spaceship adjust matrix

	Matrix world = FishScale * FishRotTrans;
	pGObj_FishLight->SetWorld(world);
	this->UpdateCollisionData(world);


	// Placing the camera relative to the spaceship
	Vect vNewCamPos = CamLookAt * FishRotTrans;		// This moves the cam position relative to ship's position and rotation
	Vect vNewLookAt = CamShipOffset * FishRotTrans;   // This moves the look-at point relative to ship's position and rotation
	SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera()->setOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera()->updateCamera();

	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_FishLight->getModel()->getRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_FishLight->getModel()->getCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	pGObj_FishBSphere->SetWorld(worldBS);
	for (auto& it : modelCol)
	{
		it->SetWorld(worldBS);
	}

	// Toggle the bounding sphere's visibility
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_SPACE))
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

void Fish::Draw()
{
	if (modelRef == modelCol.end())
	{
		forward = false; 
		modelRef--;
	}
	else if (modelRef == modelCol.begin())
	{
		forward = true;
	}

	if (moving)
	{
		this->SetColliderModel((*modelRef)->getModel());
		(*modelRef)->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());

		if (forward)
		{
			modelRef++;
		}
		else
		{
			modelRef--;
		}
	}
	else 
	{
		(*modelRef)->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	}

	if (BsphereToggle)
	{
		pGObj_FishBSphere->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
	}
} 

void Fish::KeyPressed(AZUL_KEY k)
{
	if (k == AZUL_KEY::KEY_F)
	{
		BubbleManager::ShootBubble(FishRotTrans);
	}
}

void Fish::Alarm0()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
}

void Fish::Collision(Hydra* sf)
{
	sf; 
	DebugMsg::out("Fish Collide Hydra\n");
	FishManager::LoseHeart();
}

void Fish::Collision(Food* sf)
{
	sf;
	DebugMsg::out("Fish Collide Food\n");
	
}

Matrix Fish::GetPosition() 
{
	return FishRotTrans;
}

void Fish::SetModels()
{
	Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish1"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish2"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish3"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish4"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish5"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish6"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish7"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish8"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish9"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish10"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish11"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish12"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish13"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish14"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish15"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
	modelCol.push_back(new GraphicsObject_TextureLight(ModelManager::Get("Fish16"), ShaderManager::Get("Light"), TextureManager::Get("Calico"), LightColor, LightPos));
}