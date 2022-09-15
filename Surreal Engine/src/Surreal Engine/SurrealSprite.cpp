//SurrealSprite

#include "SurrealSprite.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "ImageManager.h"
#include "Surreal Graphics/Texture.h"

SurrealSprite::SurrealSprite()
{
	pGOSprite = nullptr; 
	pImage = nullptr;
	angle = 0.0f;
	centerX = 0.0f;
	centerY = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
}

SurrealSprite::SurrealSprite(std::string imgKey)
{
	angle = 0.0f;
	centerX = 0.0f;
	centerY = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;

	pImage = ImageManager::Get(imgKey);
	pGOSprite = new GraphicsObject_Sprite(pImage->GetTexture());
	Matrix spritescale = Matrix(SCALE, 1, 1, 1.0f);
	Matrix spriterot = Matrix(ROT_Y, 0);
	Matrix spritetrans = Matrix(TRANS, 0, 0, 0.0f);
	Matrix spriteworld = spritescale * spriterot * spritetrans;
	pGOSprite->SetWorld(spriteworld);
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

void SurrealSprite::Render()
{
	pGOSprite->Render();
}

void SurrealSprite::RenderPartialTexture()
{
	pGOSprite->RenderPartialTexture(this->pImage->GetRect());
}

void SurrealSprite::SetAngle(float a)
{
	angle = a;
	UpdateWorld();
}

void SurrealSprite::SetCenter(float offsetX, float offsetY)
{
	centerX = offsetX; 
	centerY = offsetY;
	UpdateWorld();
}

void SurrealSprite::SetPosition(float x, float y)
{
	pGOSprite->SetPosition(Vect(x, y, 0.0f, 0.0f));
	UpdateWorld();
}

void SurrealSprite::SetScaleFactor(float sX, float sY)
{
	scaleX = sX; 
	scaleY = sY;
	UpdateWorld();
}

void SurrealSprite::SetScalePixel(float width, float height)
{
	scaleX = width / pImage->GetRect()->width; 
	scaleY = height / pImage->GetRect()->height;
	UpdateWorld();
}

int SurrealSprite::GetWidth()
{
	return (int)(scaleX);
}

int SurrealSprite::GetHeight()
{
	return (int)(scaleY);
}

void SurrealSprite::UpdateWorld()
{
	Matrix scale = Matrix(SCALE, scaleX, scaleY, 1.0f);
	Matrix rot = Matrix(TRANS, -centerX, -centerY, 0.0f) * Matrix(ROT_Z, angle) * Matrix(TRANS, centerX, centerY, 0.0f);
	Matrix trans = Matrix(TRANS, pGOSprite->GetPosition());
	Matrix world = scale * rot * trans;
	pGOSprite->SetWorld(world);
}