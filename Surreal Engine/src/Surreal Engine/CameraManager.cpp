//CameraManager

#include "CameraManager.h"
#include "Surreal.h"

CameraManager::CameraManager()
{
	//---------------------------------------------------------------------------------------------------------
	// Setup the current 3D perspective Camera
	//---------------------------------------------------------------------------------------------------------

	pDefaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	pDefaultCamera->SetPerspective(35.0f, float(Surreal::GetWidth()) / float(Surreal::GetHeight()), 1.0f, 5000.0f);
	pDefaultCamera->UpdateCamera();

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(50.0f, 50.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	pDefaultCamera->SetOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	pCurrentCamera = pDefaultCamera;

	//---------------------------------------------------------------------------------------------------------
	// Setup the current 2D orthographic Camera
	//---------------------------------------------------------------------------------------------------------

	pDefault2DCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D); 
	pDefault2DCamera->SetOrthographic(0, float(Surreal::GetWidth()),
		float(Surreal::GetHeight()), 0.0f, -1.0f, 1.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	pDefault2DCamera->SetOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);
	pDefault2DCamera->UpdateCamera();  
	pCurrent2DCamera = pDefault2DCamera;
}

CameraManager::~CameraManager()
{
	delete pDefaultCamera; 
	pDefaultCamera = nullptr;

	delete pDefault2DCamera;
	pDefault2DCamera = nullptr;
}

Camera* CameraManager::GetCurrentCamera()
{
	return pCurrentCamera;
}

void CameraManager::SetCurrentCamera(Camera* pNewCam)
{
	pCurrentCamera = pNewCam;
	pCurrentCamera->UpdateCamera();
}

Camera* CameraManager::GetCurrent2DCamera()
{
	return pCurrent2DCamera;
}

void CameraManager::SetCurrent2DCamera(Camera* pNewCam)
{
	pCurrent2DCamera = pNewCam;
	pCurrent2DCamera->UpdateCamera();
}
