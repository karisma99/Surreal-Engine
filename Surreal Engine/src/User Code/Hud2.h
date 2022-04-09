// Hud2
#ifndef _Hud2
#define _Hud2

#include "../Surreal Engine/GameObject.h"
#include "AzulCore.h"
#include "Camera.h"

class SurrealSprite;
class SpriteFont;
class SpriteString;

class Hud2 : GameObject
{
public:
	Hud2();
	Hud2(const Hud2& c) = delete;
	Hud2& operator = (const Hud2& t) = delete;
	~Hud2();

private:
	virtual void Update();
	virtual void Draw2D();

	// Spaceship vars
	SurrealSprite* pLife1Sprite;
	SurrealSprite* pLife2Sprite;
	SurrealSprite* pLife3Sprite;
	SurrealSprite* pCherry1Sprite;
	SurrealSprite* pCherry2Sprite;
	SurrealSprite* pCherry3Sprite;

	SpriteFont* pFont;
	SpriteString* pHealthString;
	SpriteString* pBubbleString;
};

#endif _Hud2