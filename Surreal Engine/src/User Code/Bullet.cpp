//Bullet 


#include "Bullet.h"
#include "BulletFactory.h"
#include "../Surreal Engine/Updateable.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Alarmable.h"
#include "../Surreal Engine/SceneManager.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"


Bullet::Bullet()
{
	SPEED = 1;
	Scale.set(SCALE, 3.0f, 3.0f, 3.0f);

	Vect Blue(0.0f, 0.0f, 1.0f, 1.0f);
	pGObj_BulletSphere = new GraphicsObject_WireframeConstantColor(ModelManager::Get("Sphere"), ShaderManager::Get("ConstantColor"), Blue);
}

Bullet::~Bullet()
{
	delete pGObj_BulletSphere; 
	pGObj_BulletSphere = nullptr;
}

void Bullet::Initialize(Matrix p)
{
	this->SubmitEntry();
	Pos = p; 
	StartPos = p;
}

void Bullet::Update()
{
	Pos = Matrix(TRANS, Vect(0, 0, SPEED)) * Pos;

	Matrix world; 
	world = Scale * Pos;
	pGObj_BulletSphere->SetWorld(world);
}

void Bullet::Draw()
{
	pGObj_BulletSphere->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrentCamera());
}

void Bullet::Destroy()
{
	this->SubmitExit();
}

void Bullet::SceneEntry()
{
	Updateable::SubmitUpdateRegistration();
	Drawable::SubmitDrawRegistration();
	Alarmable::SubmitAlarmRegistration(AlarmableManager::Alarm0, 3.0f);
}

void Bullet::SceneExit()
{
	Updateable::SubmitUpdateDeregistration();
	Drawable::SubmitDrawDeregistration();
	BulletFactory::RecycleBullet(this);
}

void Bullet::Alarm0()
{
	this->Destroy();
}


void Bullet::Alarm1()
{
	this->Destroy();
}

void Bullet::SetCamera(Camera* c)
{
	this->pCam = c;
}