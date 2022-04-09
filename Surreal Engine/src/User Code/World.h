// World
#ifndef _World
#define _World

#include "../Surreal Engine/GameObject.h"

class GraphicsObject_TextureFlat;
class GraphicsObject_ColorNoTexture;
class Model;

class World : public GameObject
{
public:
	World();
	World(const World& c) = delete;
	World& operator = (const World& t) = delete;
	~World();

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);

private:
	void CreateSkybox(float scale);

	GraphicsObject_TextureFlat* pGObj_Skybox;
	Model* pSkyboxModel;
};

#endif _World