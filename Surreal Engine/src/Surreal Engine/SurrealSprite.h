// SurrealSprite

#ifndef _SurrealSprite
#define _SurrealSprite

#include "Matrix.h"
#include "Surreal Graphics/GraphicsCore.h"

class Image;

class SurrealSprite
{
public:
	SurrealSprite();
	SurrealSprite(std::string imgKey);
	SurrealSprite(const SurrealSprite& c) = delete;
	SurrealSprite& operator = (const SurrealSprite& t) = delete;
	~SurrealSprite();

	float GetAngle();
	int GetWidth(); 
	int GetHeight();
	void Render();
	void RenderPartialTexture();
	void SetAngle(float a);
	void SetCenter(float offsetX, float offsetY);
	void SetPosition(float x, float y); 
	void SetScaleFactor(float scaleX, float scaleY);
	void SetScalePixel(float width, float height);

private:
	void UpdateWorld();

	float angle; 
	float centerX; 
	float centerY; 
	float scaleX; 
	float scaleY;

	GraphicsObject_Sprite* pGOSprite;
	Image* pImage;

};

#endif _SurrealSprite