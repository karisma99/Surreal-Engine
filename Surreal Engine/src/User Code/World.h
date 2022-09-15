// World
#ifndef _World
#define _World

#include "../Surreal Engine/GameObject.h"

class GraphicsObject_TextureFlat;
class Model;
class Skybox;

class World : public GameObject
{
public:
	World();
	World(const World& c) = delete;
	World& operator = (const World& t) = delete;
	~World();

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(SURREAL_KEY k);
	virtual void KeyReleased(SURREAL_KEY k);

private:
	void CreateSkybox(float scale);

	GraphicsObject_TextureFlat* pGObj_Skybox;
	Skybox* pSkybox;
};

#endif _World