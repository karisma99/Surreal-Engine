// World2
#ifndef _World2
#define _World2

#include "../Surreal Engine/GameObject.h"

class GraphicsObject_TextureFlat;
class GraphicsObject_ColorNoTexture;

class World2 : public GameObject
{
public:
	World2();
	World2(const World2& c) = delete;
	World2& operator = (const World2& t) = delete;
	~World2();

	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(AZUL_KEY k);
	virtual void KeyReleased(AZUL_KEY k);

private:
	void CreateSkybox(float scale);
	
	GraphicsObject_TextureFlat* pGObj_Skybox;
	Model* pSkyboxModel;
};

#endif _World2