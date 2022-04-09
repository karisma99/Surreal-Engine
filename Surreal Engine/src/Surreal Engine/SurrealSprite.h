// SurrealSprite

#ifndef _SurrealSprite
#define _SurrealSprite

#include "Matrix.h"

class GraphicsObject_Sprite;
class Camera; 

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
	void Render(Camera* pCam);
	void SetAngle(float a);
	void SetCenter(float offsetX, float offsetY);
	void SetPosition(float x, float y); 
	void SetScaleFactor(float scaleX, float scaleY);
	void SetScalePixel(float width, float height);

private:
	float angle; 
	float centerX; 
	float centerY; 
	float scaleX; 
	float scaleY;

	GraphicsObject_Sprite* pGOSprite;

};

#endif _SurrealSprite