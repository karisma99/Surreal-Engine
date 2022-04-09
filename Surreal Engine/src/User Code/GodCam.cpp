// SpaceFrigate 

#include "GodCam.h"
#include "../Surreal Engine/Surreal.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Updateable.h"
#include "../Surreal Engine/SceneManager.h"
#include "SceneOne.h"
#include "SceneTwo.h"

GodCam::GodCam()
{
	active = false;
	pCam = nullptr;
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);
	CamPos.set(50, 50, 100.0f);
	CamUp.set(0, 1, 0);
	CamDir.set(0, 0, 1);
	CamTranSpeed = 2;
	CamRotSpeed = .02f;

	Updateable::SubmitUpdateRegistration();
}

void GodCam::Activate()
{
	pCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	pCam->setViewport(0, 0, Surreal::GetWidth(), Surreal::GetHeight());
	pCam->setPerspective(35.0f, float(Surreal::GetWidth()) / float(Surreal::GetHeight()), 1.0f, 5000.0f);

	SceneManager::GetCurrentScene()->GetCameraManager()->SetCurrentCamera(pCam);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);
	CamPos.set(50, 50, 100.0f);
	CamUp.set(0, 1, 0);
	CamDir.set(0, 0, 1);
	CamTranSpeed = 2;
	CamRotSpeed = .002f;

	//		Second: we set the camera to its position and pointing toward the target
	pCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	pCam->updateCamera();

}

GodCam::~GodCam()
{	
	if (active) 
	{
		delete pCam;
		pCam = nullptr;
	}
}

void GodCam::Update()
{
	if (!active && Keyboard::GetKeyState(AZUL_KEY::KEY_0))
	{
		active = true; 
		Activate();
		DebugMsg::out("God Cam on\n");
	}

	if (active)
	{
		Movement();
	}
}

void GodCam::Draw()
{

}

void GodCam::Movement()
{
	// Camera translation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_W))
	{
		CamPos += Vect(0, 0, 1) * CamRot * CamTranSpeed;
		DebugMsg::out("Pressing W\n");
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_S))
	{
		CamPos += Vect(0, 0, 1) * CamRot * -CamTranSpeed;
		DebugMsg::out("Pressing S\n");
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_A))
	{
		CamPos += Vect(1, 0, 0) * CamRot * CamTranSpeed;
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_D))
	{
		CamPos += Vect(1, 0, 0) * CamRot * -CamTranSpeed;
	}

	// Camera Rotation movement (NOTE: This time, I'm NOT using time-based values for simplicity)
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed);
	}

	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -CamRotSpeed);
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, CamRotSpeed);
	}

	pCam->setOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	pCam->updateCamera();
}