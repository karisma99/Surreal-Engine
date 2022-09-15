// Fish
#ifndef _Fish
#define _Fish

#include "../Surreal Engine/GameObject.h"
#include "Surreal Graphics/Camera.h"
#include <list>
#include "Surreal Engine/Keyboard.h"

class GraphicsObject_TextureFlat;
class GraphicsObject_ColorFlat;
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
	virtual void CollisionTerrain();
	Matrix GetPosition();

private:

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(SURREAL_KEY k);
	virtual void Alarm0();
	virtual void Alarm1();

	void SetModels();
	void CheckModelSwitch();

	GraphicsObject_TextureFlat* pGObj_FishLight;
	GraphicsObject_ColorFlat* pGObj_FishBSphere;

	using ModelCollection = std::list<GraphicsObject_TextureFlat*>;
	ModelCollection modelCol;

	using ModelCollectionRef = ModelCollection::iterator;

	// Fish vars
	Matrix FishScale;
	Matrix FishRotTrans;
	const float FishTransSpeed = 300.0f;
	const float FishRotAng = 2.0f;
	bool BsphereToggle = false;
	Vect CamLookAt;
	Vect CamShipOffset;

	GraphicsObject_TextureFlat* currentObject;
	ModelCollectionRef modelRef;
	bool moving;
	bool forward;
};

#endif _Fish