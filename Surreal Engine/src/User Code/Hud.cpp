// Hud 

#include "Hud.h"
#include "Surreal Engine/ModelManager.h"
#include "Surreal Engine/ShaderManager.h"
#include "Surreal Engine/TextureManager.h"
#include "Surreal Engine/CameraManager.h"
#include "Surreal Engine/Drawable.h"
#include "Surreal Engine/Updateable.h"
#include "Surreal Engine/Alarmable.h"
#include "Surreal Engine/Inputable.h"
#include "Surreal Engine/Collidable.h"
#include "Surreal Engine/SceneManager.h"
#include "BulletFactory.h"
#include "Surreal Engine/Visualizer.h"
#include "Surreal Engine/SurrealSprite.h"
#include "Surreal Engine/SpriteFontManager.h"
#include "Surreal Engine/SpriteString.h"
#include "Surreal Engine/Surreal.h"
#include "BubbleManager.h"
#include "FishManager.h"

Hud::Hud()
{
	pLife1Sprite = new SurrealSprite("Heart");
	pLife1Sprite->SetAngle(0);
	pLife1Sprite->SetScaleFactor(50, 50);
	pLife1Sprite->SetPosition(30, (float)(Surreal::GetHeight() - 30));

	pLife2Sprite = new SurrealSprite("Heart");
	pLife2Sprite->SetAngle(0);
	pLife2Sprite->SetScaleFactor(50, 50);
	pLife2Sprite->SetPosition(90, (float)(Surreal::GetHeight() - 30));

	pLife3Sprite = new SurrealSprite("Heart");
	pLife3Sprite->SetAngle(0);
	pLife3Sprite->SetScaleFactor(50, 50);
	pLife3Sprite->SetPosition(150, (float)(Surreal::GetHeight() - 30));

	pBubble1Sprite = new SurrealSprite("Bubble");
	pBubble1Sprite->SetAngle(0);
	pBubble1Sprite->SetScaleFactor(75, 75);
	pBubble1Sprite->SetPosition(640, (float)(Surreal::GetHeight() - 30));

	pBubble2Sprite = new SurrealSprite("Bubble");
	pBubble2Sprite->SetAngle(0);
	pBubble2Sprite->SetScaleFactor(75, 75);
	pBubble2Sprite->SetPosition(640 + 65, (float)(Surreal::GetHeight() - 30));

	pBubble3Sprite = new SurrealSprite("Bubble");
	pBubble3Sprite->SetAngle(0);
	pBubble3Sprite->SetScaleFactor(75, 75);
	pBubble3Sprite->SetPosition(640 + 130, (float)(Surreal::GetHeight() - 30));
	
	pFont = SpriteFontManager::Get("Font1");
	pHealthString = new SpriteString(pFont, "Health", 50, Surreal::GetHeight() - 100);
	pBubbleString = new SpriteString(pFont, "Bubbles", 600, Surreal::GetHeight() - 60);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();
}

Hud::~Hud()
{
	delete pLife1Sprite;
	delete pLife2Sprite;
	delete pLife3Sprite;
	delete pBubble1Sprite;
	delete pBubble2Sprite;
	delete pBubble3Sprite;


	delete pHealthString; 
	delete pBubbleString;
}

void Hud::Update()
{


}

void Hud::Draw2D()
{
	pHealthString->Render();
	pBubbleString->Render();

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

	if (BubbleManager::GetBubbleCount() >= 3)
	{
		pBubble1Sprite->Render();
		pBubble2Sprite->Render();
		pBubble3Sprite->Render();
	}
	else if (BubbleManager::GetBubbleCount() == 2)
	{
		pBubble1Sprite->Render();
		pBubble2Sprite->Render();
	}
	else if (BubbleManager::GetBubbleCount() == 1)
	{
		pBubble1Sprite->Render();
	}
	
}
