// SpriteString

#ifndef _SpriteString
#define _SpriteString

#include "Matrix.h"
#include "SpriteFont.h"
#include "SurrealSprite.h"
#include <vector>

class GraphicsObject_Sprite;
class Camera;

class SpriteString
{
private:
	using GlyphCollection = std::vector<SurrealSprite*>;
	GlyphCollection glyphs;

public:
	SpriteString();
	SpriteString(const SpriteFont&);
	SpriteString(SpriteFont* sf, std::string s, int x, int y);
	SpriteString(const SpriteString& c) = delete;
	SpriteString& operator = (const SpriteString& t) = delete;
	~SpriteString() = default;

	int GetHeight();
	int GetWidth();
	void Render();
	void Set(int x, int y);
	void Set(SpriteFont* sf, std::string s, int x, int y);

private:

	int posX;
	int posY;
	int height;
	int width;

	SpriteFont* pFont;

};

#endif _SpriteString