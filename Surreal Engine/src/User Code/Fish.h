// SpaceFrigate
#ifndef _Fish
#define _Fish

#include "../Surreal Engine/GameObject.h"
#include "AzulCore.h"
#include "Camera.h"
#include <list>

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;
class Hydra;
class Food;

class Fish : public GameObject
{
public:
	Fish();
	Fish(const Fish& c) = delete;
	Fish& operator = (const Fish& t) = delete;
	~Fish();

	void Collision(Hydra*);
	void Collision(Food*);
	Matrix GetPosition();

private:

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void Alarm0();

	void SetModels();

	GraphicsObject_TextureLight* pGObj_FishLight;
	GraphicsObject_WireframeConstantColor* pGObj_FishBSphere;

	using ModelCollection = std::list<GraphicsObject_TextureLight*>;
	ModelCollection modelCol;

	using ModelCollectionRef = ModelCollection::iterator;

	// Fish vars
	Matrix FishScale;
	Matrix FishRotTrans;
	const float FishTransSpeed = 0.1f;
	const float FishRotAng = .001f;
	bool BsphereToggle = false;
	Vect CamLookAt;
	Vect CamShipOffset;

	ModelCollectionRef modelRef;
	bool moving;
	bool forward;
};

#endif _Fish