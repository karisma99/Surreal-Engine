//SurrealSprite

#include "SurrealSprite.h"
#include "GraphicsObject_Sprite.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ImageManager.h"

SurrealSprite::SurrealSprite()
{
	pGOSprite = nullptr; 
}

SurrealSprite::SurrealSprite(std::string imgKey)
{
	Image* pImage = ImageManager::Get(imgKey);
	pGOSprite = new GraphicsObject_Sprite(ModelManager::Get("UnitSquare"), ShaderManager::Get("spriteRender"), pImage, pImage->pImageRect);
}

SurrealSprite::~SurrealSprite()
{
	delete pGOSprite;
	pGOSprite = nullptr;
}

float SurrealSprite::GetAngle()
{
	return angle;
}

void SurrealSprite::Render(Camera* pCam)
{
	Matrix world = Matrix(SCALE, scaleX, scaleY, 1.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, pGOSprite->origPosX, pGOSprite->origPosY, 0.0f);

	pGOSprite->SetWorld(world);
	pGOSprite->Render(pCam);
}

void SurrealSprite::SetAngle(float a)
{
	angle = a;
}

void SurrealSprite::SetCenter(float offsetX, float offsetY)
{
	centerX = offsetX; 
	centerY = offsetY;
}

void SurrealSprite::SetPosition(float x, float y)
{
	pGOSprite->origPosX = x; 
	pGOSprite->origPosY = y; 
}

void SurrealSprite::SetScaleFactor(float sX, float sY)
{
	scaleX = sX; 
	scaleY = sY;
}

void SurrealSprite::SetScalePixel(float width, float height)
{
	scaleX = width / pGOSprite->origWidth; 
	scaleY = height / pGOSprite->origHeight;
}

int SurrealSprite::GetWidth()
{
	return (int)pGOSprite->origWidth;
}

int SurrealSprite::GetHeight()
{
	return (int)pGOSprite->origHeight;
}