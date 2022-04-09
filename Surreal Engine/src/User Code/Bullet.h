//Bullet 

#ifndef _Bullet
#define _Bullet

#include "AzulCore.h"
#include "../Surreal Engine/GameObject.h"

class GraphicsObject_WireframeConstantColor;

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();

	void Initialize(Matrix p);
	void SetCamera(Camera* c);

private:
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();

	virtual void SceneEntry();
	virtual void SceneExit();

	void Destroy();

	float SPEED;

	Matrix Scale;
	Matrix Pos;
	Matrix StartPos; 
	Vect Direction;
	GraphicsObject_WireframeConstantColor* pGObj_BulletSphere;
	Camera* pCam;
};

#endif _Bullet