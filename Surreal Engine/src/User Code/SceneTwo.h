#ifndef _SceneTwo
#define _SceneTwo

#include "../Surreal Engine/Scene.h"

class World2;
class Fish;
class GodCam;
class Hud2;
class Bubble;

class SceneTwo : public Scene
{
public:

	SceneTwo() = default;
	SceneTwo(const SceneTwo& c) = delete;
	SceneTwo& operator = (const SceneTwo& t) = delete;
	~SceneTwo() = default;


	virtual void Initialize();
	virtual void SceneEnd();

private:

	World2* pWorld;
	Fish* pFish;
	GodCam* pGodCam;
	Hud2* pHud;

};

#endif _SceneTwo