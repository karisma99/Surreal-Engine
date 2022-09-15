// World2
#ifndef _World2
#define _World2

#include "../Surreal Engine/GameObject.h"

class GraphicsObject_TextureFlat;
class Model;
class Skybox;

class World2 : public GameObject
{
public:
	World2();
	World2(const World2& c) = delete;
	World2& operator = (const World2& t) = delete;
	~World2();

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(SURREAL_KEY k);
	virtual void KeyReleased(SURREAL_KEY k);

private:
	void CreateSkybox(float scale);
	
	GraphicsObject_TextureFlat* pGObj_Skybox;
	Skybox* pSkybox;
};

#endif _World2