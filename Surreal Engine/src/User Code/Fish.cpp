// Fish 

#include "Fish.h"
#include "Surreal Engine/ModelManager.h"
#include "Surreal Engine/ShaderManager.h"
#include "Surreal Engine/TextureManager.h"
#include "Surreal Engine/CameraManager.h"
#include "Surreal Engine/Drawable.h"
#include "Surreal Engine/Updateable.h"
#include "Surreal Engine/Alarmable.h"
#include "Surreal Engine/SceneManager.h"
#include "User Code/BubbleManager.h"
#include "User Code/FishManager.h"
#include "Surreal Engine/Colors.h"
#include "Surreal Engine/TimeManager.h"
#include "Surreal Engine/TerrainObject.h"

Fish::Fish()
{
	pGObj_FishLight = new GraphicsObject_TextureFlat(ModelManager::Get("Fish"), TextureManager::Get("Calico"));
	currentObject = pGObj_FishLight;
	pGObj_FishBSphere = new GraphicsObject_ColorFlat(ModelManager::Get("Sphere"), Color::Blue);

	// Spaceship
	FishScale.set(SCALE, 30.0f, 7.0f, 10.0f);
	FishRotTrans = Matrix(ROT_Y, 135) * Matrix(TRANS, 0, 20, 0);

	// Creating matrices for in-world placement
	Matrix world;
	world = FishScale * FishRotTrans;
	pGObj_FishLight->SetWorld(world);

	CamShipOffset.set(-50, -50, 0);
	CamLookAt.set(0, 10, 0);

	SetModels(); 
	modelRef = modelCol.begin();
	moving = false;
	forward = true;
	
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Inputable::SubmitKeyRegistration(SURREAL_KEY::F_KEY, EventType::KEY_PRESS);
	//Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm0, 3.0f);
	Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm1, 60.0f * TimeManager::GetFrameTime());

	Collidable::SetCollidableGroup<Fish>(); 
	Collidable::SubmitCollisionRegistration(); 
	this->SetColliderModel(pGObj_FishLight->GetModel(), AABB);
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
	if (Keyboard::GetKeyInputState(SURREAL_KEY::J_KEY))
	{
		FishRotTrans = Matrix(ROT_Y, -FishRotAng * TimeManager::GetFrameTime()) * FishRotTrans;
		moving = true;
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::L_KEY))
	{
		FishRotTrans = Matrix(ROT_Y, FishRotAng * TimeManager::GetFrameTime()) * FishRotTrans;
		moving = true;
	}

	if (Keyboard::GetKeyInputState(SURREAL_KEY::I_KEY))
	{
		FishRotTrans = Matrix(TRANS, Vect(FishTransSpeed * TimeManager::GetFrameTime(), 0, 0)) * FishRotTrans;
		moving = true;
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::K_KEY))
	{
		FishRotTrans = Matrix(TRANS, Vect(-FishTransSpeed * TimeManager::GetFrameTime(), 0, 0)) * FishRotTrans;
		moving = true;
	}

	// Fish adjust matrix
	Matrix world;
	Vect vNewCamPos;
	Vect vNewLookAt;
	if (SceneManager::GetCurrentScene()->GetTerrain())
	{
		float offset = 50;
		Vect terrainCellCenter = SceneManager::GetCurrentScene()->GetTerrain()->GetCellCenterAtPosition(Vect(FishRotTrans.M12(), FishRotTrans.M13(), FishRotTrans.M14()));
		//FishRotTrans = Matrix(TRANS, 0, terrainCellCenter.Y() + offset, 0) * FishRotTrans;

		//// Rotate according to terrain
		//Vect terrainNormal = SceneManager::GetCurrentScene()->GetTerrain()->GetTerrainNormalAtPosition(Vect(FishRotTrans.M12(), FishRotTrans.M13(), FishRotTrans.M14()));
		//Vect r = terrainNormal.cross(FishRotTrans.get(ROW_2));
		//Vect fwd = r.cross(terrainNormal);
		//FishRotTrans = Matrix(ROT_ORIENT, fwd, terrainNormal) * Matrix(TRANS, FishRotTrans.get(ROW_3));

		world = FishScale * FishRotTrans * Matrix(TRANS, 0, terrainCellCenter.Y() - offset, 0);
		vNewCamPos = CamLookAt * FishRotTrans * Matrix(TRANS, 0, terrainCellCenter.Y() - offset, 0);
		vNewLookAt = CamShipOffset * FishRotTrans * Matrix(TRANS, 0, terrainCellCenter.Y() - offset, 0);
	}
	else
	{
		world = FishScale * FishRotTrans;
		vNewCamPos = CamLookAt * FishRotTrans;
		vNewLookAt = CamShipOffset * FishRotTrans;
	}

	
	pGObj_FishLight->SetWorld(world);
	this->UpdateCollisionData(world);


	// Placing the camera relative to the spaceship
	SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera()->SetOrientAndPosition(Vect(0, 1, 0), vNewCamPos, vNewLookAt);
	SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera()->UpdateCamera();

	//*
	// Adjusting the spaceship's bounding sphere
	Vect vBSSize = pGObj_FishLight->GetModel()->GetRadius() * Vect(1, 1, 1);
	Vect vBSPos = pGObj_FishLight->GetModel()->GetCenter();

	// Adjust the Bounding Sphere's position and scale to fit the Ship's center and scale
	Matrix worldBS = Matrix(SCALE, vBSSize) * Matrix(TRANS, vBSPos) * world;

	pGObj_FishBSphere->SetWorld(worldBS);
	for (auto& it : modelCol)
	{
		it->SetWorld(worldBS);
	}

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

void Fish::Draw()
{
	currentObject->Render();

	if (BsphereToggle)
	{
		pGObj_FishBSphere->RenderWireframe();
	}
} 

void Fish::KeyPressed(SURREAL_KEY k)
{
	if (k == SURREAL_KEY::F_KEY)
	{
		BubbleManager::ShootBubble(FishRotTrans);
	}
}

void Fish::Alarm0()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
}

void Fish::Alarm1()
{
	CheckModelSwitch();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm1, 60.0f * TimeManager::GetFrameTime());
}

void Fish::Collision(Hydra* sf)
{
	sf; 
	Trace::out("Fish Collide Hydra\n");
	FishManager::LoseHeart();
}

void Fish::Collision(Food* sf)
{
	sf;
	Trace::out("Fish Collide Food\n");
	
}

void Fish::CollisionTerrain()
{
	Trace::out("Fish Collide Terrain\n");
}

Matrix Fish::GetPosition() 
{
	return FishRotTrans;
}

void Fish::CheckModelSwitch()
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
		currentObject = *modelRef;

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
		currentObject = *modelRef;
	}
}

void Fish::SetModels()
{	
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish1"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish2"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish3"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish4"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish5"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish6"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish7"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish8"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish9"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish10"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish11"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish12"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish13"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish14"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish15"), TextureManager::Get("Calico")));
	modelCol.push_back(new GraphicsObject_TextureFlat(ModelManager::Get("Fish16"), TextureManager::Get("Calico")));
}