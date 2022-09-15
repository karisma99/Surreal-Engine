// Hydra
#ifndef _Hydra
#define _Hydra

#include "Surreal Engine/GameObject.h"
class GraphicsObject_TextureFlat;
class GraphicsObject_ColorFlat;
class Fish;
class Bubble;

class Hydra : public GameObject
{
public:
	Hydra();
	Hydra(const Hydra& c) = delete;
	Hydra& operator = (const Hydra& t) = delete;
	~Hydra();

	void Collision(Fish*);
	void Collision(Bubble*);

	void Initialize(Matrix m);

private:
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void SceneEntry();
	virtual void SceneExit();

	void FacePlayer();
	void Destroy();

	GraphicsObject_TextureFlat* pGObj_SpaceFrigateLight;
	GraphicsObject_ColorFlat* pGObj_SpaceshipBSphere;

	Matrix HydraScale;
	Matrix HydraRotTrans;
	Matrix Direction;
	const float HydraSpeed = 225.0f;;
	const float HydraRotAng = .05f;
	bool BsphereToggle = false;
	Vect CamLookAt;
	Vect CamShipOffset;
};

#endif _Hydra