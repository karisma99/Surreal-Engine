//Food 

#ifndef _Food
#define _Food

#include "AzulCore.h"
#include "../Surreal Engine/GameObject.h"

class GraphicsObject_ColorNoTexture;
class Fish;
class FoodFactory;

class Food : public GameObject
{
public:
	Food();
	~Food();

	void Initialize(Matrix p);

	virtual void Collision(Fish*);

private:
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();

	virtual void SceneEntry();
	virtual void SceneExit();

	void Destroy();

	float SPEED;

	Matrix Scale;
	Matrix Pos;
	Matrix StartPos;
	Vect Direction;
	GraphicsObject_ColorNoTexture* pGObj_BubbleSphere;
};

#endif _Food