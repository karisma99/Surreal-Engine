// CameraManager.h

#ifndef _CameraManager
#define _CameraManager

#include "Camera.h"

class Camera;

class CameraManager
{
	friend class CameraManagerAttorney;
public:
	CameraManager();
	CameraManager(const CameraManager& c) = delete;
	CameraManager& operator = (const CameraManager& t) = delete;
	~CameraManager();

	Camera* GetCurrentCamera();
	void SetCurrentCamera(Camera* newCam);

	Camera* GetCurrent2DCamera();
	void SetCurrent2DCamera(Camera* newCam);

private:
	Camera* pDefaultCamera;
	Camera* pCurrentCamera;
	Camera* pDefault2DCamera;
	Camera* pCurrent2DCamera;

};

#endif _CameraManager