// Hud
#ifndef _Hud
#define _Hud

#include "Surreal Engine/GameObject.h"
#include "Surreal Graphics/Camera.h"

class SurrealSprite;
class SpriteFont;
class SpriteString;

class Hud : GameObject
{
public:
	Hud();
	Hud(const Hud& c) = delete;
	Hud& operator = (const Hud& t) = delete;
	~Hud();

private:
	virtual void Update();
	virtual void Draw2D();

	// Spaceship vars
	SurrealSprite* pLife1Sprite;
	SurrealSprite* pLife2Sprite;
	SurrealSprite* pLife3Sprite;
	SurrealSprite* pBubble1Sprite;
	SurrealSprite* pBubble2Sprite;
	SurrealSprite* pBubble3Sprite;

	SpriteFont* pFont;
	SpriteString* pHealthString;
	SpriteString* pBubbleString;
};

#endif _Hud