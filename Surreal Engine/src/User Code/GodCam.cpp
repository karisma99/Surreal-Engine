// GodCam 

#include "GodCam.h"
#include "Surreal Engine/Surreal.h"
#include "Surreal Engine/CameraManager.h"
#include "Surreal Engine/Drawable.h"
#include "Surreal Engine/Updateable.h"
#include "Surreal Engine/SceneManager.h"
#include "Surreal Engine/TimeManager.h"
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
	pCam->SetPerspective(35.0f, float(Surreal::GetWidth()) / float(Surreal::GetHeight()), 1.0f, 5000.0f);

	SceneManager::GetCurrentScene()->GetCameraManager()->SetCurrentCamera(pCam);

	// Position and Orient Camera
	//      First: we create a rotation matrix pointing (Z) towards the target
	Vect Target(0, 0, 0);
	CamRot.set(ROT_ORIENT, Target - CamPos, CamUp);
	CamPos.set(50, 50, 100.0f);
	CamUp.set(0, 1, 0);
	CamDir.set(0, 0, 1);
	CamTranSpeed = 300.0f;
	CamRotSpeed = 2.0f;;

	//		Second: we set the camera to its position and pointing toward the target
	pCam->SetOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	pCam->UpdateCamera();

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
	if (!active && Keyboard::GetKeyInputState(SURREAL_KEY::NUM_0_KEY))
	{
		active = true; 
		Activate();
		Trace::out("God Cam on\n");
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
	if (Keyboard::GetKeyInputState(SURREAL_KEY::W_KEY))
	{
		CamPos += Vect(0, 0, CamTranSpeed * TimeManager::GetFrameTime()) * CamRot;
		Trace::out("Pressing W\n");
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::S_KEY))
	{
		CamPos += Vect(0, 0, -CamTranSpeed * TimeManager::GetFrameTime()) * CamRot;
		Trace::out("Pressing S\n");
	}

	if (Keyboard::GetKeyInputState(SURREAL_KEY::A_KEY))
	{
		CamPos += Vect(-CamTranSpeed * TimeManager::GetFrameTime(), 0, 0) * CamRot;
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::D_KEY))
	{
		CamPos += Vect(CamTranSpeed * TimeManager::GetFrameTime(), 0, 0) * CamRot;
	}

	// Camera Rotation movement 
	if (Keyboard::GetKeyInputState(SURREAL_KEY::ARROW_LEFT_KEY))
	{
		CamRot *= Matrix(ROT_Y, -CamRotSpeed * TimeManager::GetFrameTime());
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::ARROW_RIGHT_KEY))
	{
		CamRot *= Matrix(ROT_Y, CamRotSpeed * TimeManager::GetFrameTime());
	}

	if (Keyboard::GetKeyInputState(SURREAL_KEY::ARROW_UP_KEY))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, CamRotSpeed * TimeManager::GetFrameTime());
	}
	else if (Keyboard::GetKeyInputState(SURREAL_KEY::ARROW_DOWN_KEY))
	{
		CamRot *= Matrix(ROT_AXIS_ANGLE, Vect(1, 0, 0) * CamRot, -CamRotSpeed * TimeManager::GetFrameTime());
	}

	pCam->SetOrientAndPosition(CamUp * CamRot, CamPos + CamDir * CamRot, CamPos);
	pCam->UpdateCamera();
}