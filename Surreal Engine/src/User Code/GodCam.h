// GodCam
#ifndef _GodCam
#define _GodCam

#include "../Surreal Engine/GameObject.h"
#include "AzulCore.h"
#include "Camera.h"

class SceneOne;
class SceneTwo;
class SceneDemo;

class GodCam : public GameObject
{
public:
	GodCam();
	GodCam(const GodCam& c) = delete;
	GodCam& operator = (const GodCam& t) = delete;
	~GodCam();

	void Activate();

private:
	virtual void Update();
	virtual void Draw();

	void Movement();

	Camera* pCam;

	Matrix CamRot;
	Vect CamPos;
	Vect CamUp;
	Vect CamDir;
	float CamTranSpeed;
	float CamRotSpeed;
	bool active;

};

#endif _GodCam