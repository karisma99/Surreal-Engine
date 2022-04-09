#ifndef _SceneOne
#define _SceneOne

#include "../Surreal Engine/Scene.h"

class World;
class Fish;
class Hydra;
class GodCam; 
class Hud;
class Bubble;

class SceneOne : public Scene
{
public:

	SceneOne() = default;
	SceneOne(const SceneOne& c) = delete;
	SceneOne& operator = (const SceneOne& t) = delete;
	~SceneOne() = default;


	virtual void Initialize();
	virtual void SceneEnd();

private:

	World* pWorld;
	Fish* pFish;
	Hydra* pHydra;
	GodCam* pGodCam; 
	Hud* pHud;

};

#endif _SceneOne