//Bubble 

#ifndef _Bubble 
#define _Bubble 

#include "AzulCore.h"
#include "../Surreal Engine/GameObject.h"

class GraphicsObject_WireframeConstantColor;
class SurrealSprite;
class Hydra;
class Bubble;

class Bubble : public GameObject
{
public:
	Bubble();
	~Bubble();

	void Initialize(Matrix p);

	virtual void Collision(Hydra*);

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
	GraphicsObject_WireframeConstantColor* pGObj_BubbleSphere;
};

#endif _Bubble 