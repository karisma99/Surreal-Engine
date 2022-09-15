// WorldPlane
#ifndef _WorldPlane
#define _WorldPlane

#include "Surreal Engine/GameObject.h"
#include "Surreal Engine/Keyboard.h"

class GraphicsObject_TextureFlat;
class GraphicsObject_ColorFlat;

class WorldPlane : public GameObject
{
public:
	WorldPlane();
	WorldPlane(const WorldPlane& c) = delete;
	WorldPlane& operator = (const WorldPlane& t) = delete;
	~WorldPlane();

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(SURREAL_KEY k);
	virtual void KeyReleased(SURREAL_KEY k);

	void SetCamera(Camera* c);

private:
	GraphicsObject_TextureFlat* pGObj_Plane;
	GraphicsObject_ColorFlat *pGObj_Axis;
	Camera* pCam;
};

#endif _WorldPlane