#include "Surreal Engine/Surreal.h"
#include "Surreal Engine/TextureManager.h"
#include "Surreal Engine/ShaderManager.h"
#include "Surreal Engine/ModelManager.h"
#include "Surreal Engine/SceneManager.h"
#include "Surreal Engine/CameraManager.h"
#include "Surreal Engine/ImageManager.h"
#include "Surreal Engine/SpriteFontManager.h"
#include "User Code/SceneDemo.h"
#include "User Code/SceneOne.h"
#include "Surreal Engine/TerrainObjectManager.h"

void Surreal::LoadResources()
{
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------

	// Model from file ( .azul format)
	ModelManager::Load("Axis", "Axis.azul");
	ModelManager::Load("Plane", "Plane.azul");
	ModelManager::Load("SpaceFrigate", "space_frigate.azul");
	ModelManager::Load("Sphere", Model::PreMadeModels::UnitSphere);
	ModelManager::Load("UnitSquare", Model::PreMadeModels::UnitSquare2D);
	ModelManager::Load("UnitBox", Model::PreMadeModels::UnitBox);

	ModelManager::Load("Fish", "fish.azul");
	ModelManager::Load("Fish1", "fish1.azul");
	ModelManager::Load("Fish2", "fish2.azul");
	ModelManager::Load("Fish3", "fish3.azul");
	ModelManager::Load("Fish4", "fish4.azul");
	ModelManager::Load("Fish5", "fish5.azul");
	ModelManager::Load("Fish6", "fish6.azul");
	ModelManager::Load("Fish7", "fish7.azul");
	ModelManager::Load("Fish8", "fish8.azul");
	ModelManager::Load("Fish9", "fish9.azul");
	ModelManager::Load("Fish10", "fish10.azul");
	ModelManager::Load("Fish11", "fish11.azul");
	ModelManager::Load("Fish12", "fish12.azul");
	ModelManager::Load("Fish13", "fish13.azul");
	ModelManager::Load("Fish14", "fish14.azul");
	ModelManager::Load("Fish15", "fish15.azul");
	ModelManager::Load("Fish16", "fish16.azul");
	ModelManager::Load("Hydra", "Hydra.azul");

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	// Direct loads
	TextureManager::Load("SpaceFrigate", "space_frigate.tga");
	TextureManager::Load("Grid", "grid.tga");

	TextureManager::Load("Calico", "Fish.tga");
	TextureManager::Load("HydraColor", "HydraColor.tga");
	TextureManager::Load("Heart", "Heart.tga");
	TextureManager::Load("Bubble", "Bubble.tga");
	TextureManager::Load("Cherry", "food.tga");
	TextureManager::Load("skybox", "skybox.tga");
	TextureManager::Load("heaven", "heavenSkybox.tga");
	TextureManager::Load("Gravel", "Gravel.tga");

	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------

	ShaderManager::Load("textureFlat", new ShaderTexture());
	ShaderManager::Load("textureLight", new ShaderTextureLight());
	ShaderManager::Load("colorFlat", new ShaderColor());
	ShaderManager::Load("colorLight", new ShaderColorLight());

	//---------------------------------------------------------------------------------------------------------
	// Load the Images
	//---------------------------------------------------------------------------------------------------------
	ImageManager::Load("Heart", TextureManager::Get("Heart"));
	ImageManager::Load("Bubble", TextureManager::Get("Bubble"));
	ImageManager::Load("Cherry", TextureManager::Get("Cherry"));

	//---------------------------------------------------------------------------------------------------------
	// Load the Fonts
	//---------------------------------------------------------------------------------------------------------
	SpriteFontManager::Load("Font1", "Stencil60");


	//---------------------------------------------------------------------------------------------------------
	// Load the Terrains
	//---------------------------------------------------------------------------------------------------------
	TerrainObjectManager::Load("GravelTerrain", "HMtest.tga", "Gravel", 100, 100.0f, 50.0f, 20, 20);

	//---------------------------------------------------------------------------------------------------------
	// Load Scene
	//---------------------------------------------------------------------------------------------------------
	SceneManager::SetNextScene(new SceneOne());

}