// HydraTest
#ifndef _HydraTest
#define _HydraTest

#include "../Surreal Engine/GameObject.h"
#include "AzulCore.h"
#include "Camera.h"

class GraphicsObject_TextureLight;
class GraphicsObject_WireframeConstantColor;
class SpaceFrigate;

class HydraTest : public GameObject
{
public:
	HydraTest();
	HydraTest(const HydraTest& c) = delete;
	HydraTest& operator = (const HydraTest& t) = delete;
	~HydraTest();

	void Collision(SpaceFrigate*);

	void SetCamera(Camera* c);

private:
	virtual void Update();
	virtual void Draw();
	virtual void Alarm0();
	virtual void Alarm1();

	GraphicsObject_TextureLight* pGObj_SpaceFrigateLight;
	GraphicsObject_WireframeConstantColor* pGObj_SpaceshipBSphere;

	// Spaceship vars
	Matrix ShipScale;
	Matrix ShipRotTrans;
	const float ShipTransSpeed = 1;
	const float ShipRotAng = .05f;
	bool BsphereToggle = false;
	Vect CamLookAt;
	Vect CamShipOffset;

	Camera* pCam;
};

#endif _HydraTest