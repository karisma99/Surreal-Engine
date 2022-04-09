//Bubble

#include "Food.h"
#include "BubbleFactory.h"
#include "../Surreal Engine/Updateable.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Alarmable.h"
#include "../Surreal Engine/Collidable.h"
#include "../Surreal Engine/SceneManager.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/SurrealSprite.h"
#include "../User Code/FoodFactory.h"
#include "../User Code/FoodManager.h"


Food::Food()
{
	SPEED = 0.5f;
	Scale.set(SCALE, 5.0f, 5.0f, 5.0f);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_BubbleSphere = new GraphicsObject_ColorNoTexture(ModelManager::Get("Sphere"), ShaderManager::Get("ColorNoTex"));
	Collidable::SetCollidableGroup<Food>();
	this->SetColliderModel(pGObj_BubbleSphere->getModel());
}

Food::~Food()
{
	delete pGObj_BubbleSphere;
	pGObj_BubbleSphere = nullptr;
}

void Food::Initialize(Matrix p)
{
	this->SubmitEntry();
	Pos = p;
	StartPos = p;

	Matrix world;
	world = Scale * Pos;
	pGObj_BubbleSphere->SetWorld(world);
	this->UpdateCollisionData(world);
}

void Food::Update()
{
	
}

void Food::Draw()
{
	pGObj_BubbleSphere->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void Food::Destroy()
{
	this->SubmitExit();
}

void Food::Collision(Fish* sf)
{
	sf;
	DebugMsg::out("Bubble Collide Hydra\n");
	FoodManager::EatFood();
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::Alarm0);
	Destroy();
}

void Food::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm0, 2.0f);
}

void Food::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	FoodFactory::RecycleFood(this);
}

void Food::Alarm0()
{
	this->Destroy();
}