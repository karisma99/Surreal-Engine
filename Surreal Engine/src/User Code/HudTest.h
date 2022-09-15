// HudTest
#ifndef _HudTest
#define _HudTest

#include "Surreal Engine/GameObject.h"
#include "Surreal Graphics/Camera.h"

class SurrealSprite;

class HudTest : GameObject
{
public:
	HudTest();
	HudTest(const HudTest& c) = delete;
	HudTest& operator = (const HudTest& t) = delete;
	~HudTest();

private:
	virtual void Update();
	virtual void Draw2D();

	// Spaceship vars
	SurrealSprite* pLifeSprite; 
};

#endif _HudTest