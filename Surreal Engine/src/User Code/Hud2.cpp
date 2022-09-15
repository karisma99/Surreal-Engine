// Hud2 

#include "Hud2.h"
#include "../Surreal Engine/ModelManager.h"
#include "../Surreal Engine/ShaderManager.h"
#include "../Surreal Engine/TextureManager.h"
#include "../Surreal Engine/CameraManager.h"
#include "../Surreal Engine/Drawable.h"
#include "../Surreal Engine/Updateable.h"
#include "../Surreal Engine/Alarmable.h"
#include "../Surreal Engine/Inputable.h"
#include "../Surreal Engine/Collidable.h"
#include "../Surreal Engine/SceneManager.h"
#include "BulletFactory.h"
#include "../Surreal Engine/Visualizer.h"
#include "../Surreal Engine/SurrealSprite.h"
#include "../Surreal Engine/SpriteFontManager.h"
#include "../Surreal Engine/SpriteString.h"
#include "../User Code/FishManager.h"
#include "../User Code/FoodManager.h"

Hud2::Hud2()
{
	pLife1Sprite = new SurrealSprite("Heart");
	pLife1Sprite->SetAngle(0);
	pLife1Sprite->SetScalePixel(50, 50);
	pLife1Sprite->SetPosition(30, 30);

	pLife2Sprite = new SurrealSprite("Heart");
	pLife2Sprite->SetAngle(0);
	pLife2Sprite->SetScalePixel(50, 50);
	pLife2Sprite->SetPosition(90, 30);

	pLife3Sprite = new SurrealSprite("Heart");
	pLife3Sprite->SetAngle(0);
	pLife3Sprite->SetScalePixel(50, 50);
	pLife3Sprite->SetPosition(150, 30);

	pCherry1Sprite = new SurrealSprite("Cherry");
	pCherry1Sprite->SetAngle(0);
	pCherry1Sprite->SetScalePixel(75, 75);
	pCherry1Sprite->SetPosition(650, 30);

	pCherry2Sprite = new SurrealSprite("Cherry");
	pCherry2Sprite->SetAngle(0);
	pCherry2Sprite->SetScalePixel(75, 75);
	pCherry2Sprite->SetPosition(650 + 60, 30);

	pCherry3Sprite = new SurrealSprite("Cherry");
	pCherry3Sprite->SetAngle(0);
	pCherry3Sprite->SetScalePixel(75, 75);
	pCherry3Sprite->SetPosition(650 + 120, 30);

	pFont = SpriteFontManager::Get("Font1");
	pHealthString = new SpriteString(pFont, "Health", 50, 100);
	pBubbleString = new SpriteString(pFont, "Food", 600, 60);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();
}

Hud2::~Hud2()
{
	delete pLife1Sprite;
	delete pLife2Sprite;
	delete pLife3Sprite;
	delete pCherry1Sprite;
	delete pCherry2Sprite;
	delete pCherry3Sprite;


	delete pHealthString;
	delete pBubbleString;
}

void Hud2::Update()
{


}

void Hud2::Draw2D()
{
	//pHealthString->Render();
	//pBubbleString->Render();

	if (FishManager::GetHeartCount() >= 3)
	{
		pLife1Sprite->Render();
		pLife2Sprite->Render();
		pLife3Sprite->Render();
	}
	else if (FishManager::GetHeartCount() == 2)
	{
		pLife1Sprite->Render();
		pLife2Sprite->Render();
	}
	else if (FishManager::GetHeartCount() == 1)
	{
		pLife1Sprite->Render();
	}

	if (FoodManager::GetGoodEatenCount() >= 3)
	{
		pCherry1Sprite->Render();
		pCherry2Sprite->Render();
		pCherry3Sprite->Render();
	}
	else if (FoodManager::GetGoodEatenCount() == 2)
	{
		pCherry1Sprite->Render();
		pCherry2Sprite->Render();
	}
	else if (FoodManager::GetGoodEatenCount() == 1)
	{
		pCherry1Sprite->Render();
	}

}
