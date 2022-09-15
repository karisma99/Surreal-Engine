#include "Surreal.h"
#include "ShaderManagerAttorney.h"
#include "TextureManagerAttorney.h"
#include "ModelManagerAttorney.h"
#include "CameraManagerAttorney.h"
#include "SceneManagerAttorney.h"
#include "TimeManagerAttorney.h"
#include "VisualizerAttorney.h"
#include "ImageManagerAttorney.h"
#include "SpriteFontManagerAttorney.h"
#include "ScreenLogAttorney.h"
#include "Surreal Graphics/GPUController.h"
#include "Surreal Graphics/WindowController.h"
#include "TerrainObjectManagerAttorney.h"

Surreal* Surreal::ptrInstance = nullptr;

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Surreal::privInitialize(HWND hwnd)
{
	//Directx 11 init
	assert(hwnd);
	RECT rc;
	BOOL err = GetClientRect(hwnd, &rc);
	assert(err);
	int mClientWidth = rc.right - rc.left;
	int mClientHeight = rc.bottom - rc.top;
	GPUController::InitDirect3D(hwnd, mClientWidth, mClientHeight);

	// Surreal Window Device setup
	GameInitialize();
	this->LoadResources();
	SceneManagerAttorney::GameLoop::StartScene();
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Surreal::privUpdate()
{
	TimeManagerAttorney::ProcessTime();
	SceneManagerAttorney::GameLoop::Update();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Surreal::privDraw()
{
	GPUController::ResetContext();
	VisualizerAttorney::GameLoop::VisualizeAll();
	SceneManagerAttorney::GameLoop::Draw();
	ScreenLogAttorney::Render();
	GPUController::SwapChainSwitch();
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Surreal::privUnLoadContent()
{
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();
	TerrainObjectManagerAttorney::Delete();

	SceneManagerAttorney::GameLoop::Delete();
	TimeManagerAttorney::Delete();
	VisualizerAttorney::GameLoop::Delete();
	ScreenLogAttorney::Delete();

	GameEnd(); 
}

void Surreal::privDelete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}

float Surreal::privGetTimeInSeconds()
{
	return TimeManager::GetTime();
}

int Surreal::privGetWidth()
{
	return WindowController::GetWindowWidth();
}

int Surreal::privGetHeight()
{
	return WindowController::GetWindowHeight();
}

void Surreal::privSetWindowName(const char* name)
{
	WindowController::SetWindowName(name);
}

void Surreal::privSetWidthHeight(int w, int h)
{
	WindowController::SetWindowWidthHeight(w, h);
}

void Surreal::privSetClearColor(float r, float g, float b, float a)
{
	r; g; b; a;
}


