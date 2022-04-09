#ifndef _SceneDemo
#define _SceneDemo

#include "../Surreal Engine/Scene.h"

class WorldPlane;
class SpaceFrigate;
class Bullet;
class HydraTest;
class HudTest; 

class SceneDemo : public Scene
{
public:

	SceneDemo() = default;
	SceneDemo(const SceneDemo& c) = delete;
	SceneDemo& operator = (const SceneDemo& t) = delete;
	~SceneDemo() = default;


	virtual void Initialize();
	virtual void SceneEnd();
	
	void SetCamera(); 

private:

	WorldPlane* pWorldPlane;
	SpaceFrigate* pFrigate;
	SpaceFrigate* pFrigate2;
	HydraTest* pHydra;
	HudTest* pHud;

};

#endif _SceneDemo