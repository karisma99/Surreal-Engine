#include "AzulCore.h"
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

Surreal* Surreal::ptrInstance = nullptr;

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Surreal::Initialize()
{
	// Surreal Window Device setup
	GameInitialize();
	// Use this area, for one time non-graphic creation
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Surreal::LoadContent()
{
	ShaderManagerAttorney::LoadDefaultShaders();
	this->LoadResources();
	SceneManagerAttorney::GameLoop::StartScene();
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Surreal::Update()
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
void Surreal::Draw()
{
	VisualizerAttorney::GameLoop::VisualizeAll();
	SceneManagerAttorney::GameLoop::Draw();
	ScreenLogAttorney::Render();
}

//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Surreal::UnLoadContent()
{
	ShaderManagerAttorney::Delete();
	TextureManagerAttorney::Delete();
	ModelManagerAttorney::Delete();
	ImageManagerAttorney::Delete();
	SpriteFontManagerAttorney::Delete();

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


