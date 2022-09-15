// SpaceFrigate
#ifndef _SpaceFrigate
#define _SpaceFrigate

#include "../Surreal Engine/GameObject.h"
#include "Surreal Graphics/Camera.h"

class GraphicsObject_TextureFlat;
class GraphicsObject_ColorFlat;
class HydraTest;

class SpaceFrigate : public GameObject
{
public:
	SpaceFrigate();
	SpaceFrigate(const SpaceFrigate& c) = delete;
	SpaceFrigate& operator = (const SpaceFrigate& t) = delete;
	~SpaceFrigate();

	void Collision(SpaceFrigate*);
	void Collision(HydraTest*);

	void SetCamera(Camera* c);

private:
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();
	virtual void KeyPressed(SURREAL_KEY k);

	GraphicsObject_TextureFlat* pGObj_SpaceFrigateLight;
	GraphicsObject_ColorFlat* pGObj_SpaceshipBSphere;

	// Spaceship vars
	Matrix ShipScale;
	Matrix ShipRotTrans;
	const float ShipTransSpeed = 0.1f;
	const float ShipRotAng = .001f;
	bool BsphereToggle = false;
	Vect CamLookAt;
	Vect CamShipOffset; 

	Camera* pCam; 
};

#endif _SpaceFrigate