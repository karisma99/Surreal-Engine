//Bubble

#include "Bubble.h"
#include "BubbleFactory.h"
#include "Surreal Engine/Updateable.h"
#include "Surreal Engine/Drawable.h"
#include "Surreal Engine/Alarmable.h"
#include "Surreal Engine/Collidable.h"
#include "Surreal Engine/SceneManager.h"
#include "Surreal Engine/ModelManager.h"
#include "Surreal Engine/ShaderManager.h"
#include "Surreal Engine/TextureManager.h"
#include "Surreal Engine/CameraManager.h"
#include "Surreal Engine/SurrealSprite.h"
#include "Surreal Engine/TimeManager.h"


Bubble::Bubble()
{
	SPEED = 350.0f;;
	Scale.set(SCALE, 2.0f, 2.0f, 2.0f);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_BubbleSphere = new GraphicsObject_ColorFlat(ModelManager::Get("Sphere"), Blue);
	Collidable::SetCollidableGroup<Bubble>();
	this->SetColliderModel(pGObj_BubbleSphere->GetModel(), BSPHERE);
}

Bubble::~Bubble()
{
	delete pGObj_BubbleSphere;
	pGObj_BubbleSphere = nullptr;
}

void Bubble::Initialize(Matrix p)
{
	this->SubmitEntry();
	Pos = p; 
	StartPos = p;
}

void Bubble::Update()
{
	Pos = Matrix(TRANS, Vect(SPEED * TimeManager::GetFrameTime(), 0, 0)) * Pos;

	Matrix world; 
	world = Scale * Pos;
	pGObj_BubbleSphere->SetWorld(world);
	this->UpdateCollisionData(world);
}

void Bubble::Draw()
{
	pGObj_BubbleSphere->Render();
}

void Bubble::Destroy()
{
	this->SubmitExit();
}

void Bubble::Collision(Hydra* sf)
{
	sf;
	Trace::out("Bubble Collide Hydra\n");
	Alarmable::SubmitAlarmDeregistration(AlarmableManager::Alarm0);
	Destroy();
}

void Bubble::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Collidable::SubmitCollisionRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm0, 3.0f);
}

void Bubble::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	Collidable::SubmitCollisionDeregistration();
	BubbleFactory::RecycleBubble(this);
}

void Bubble::Alarm0()
{
	this->Destroy();
}