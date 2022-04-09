// HudTest 

#include "HudTest.h"
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

HudTest::HudTest()
{
	pLifeSprite = new SurrealSprite("Heart");

	pLifeSprite->SetAngle(0);
	pLifeSprite->SetScalePixel(50, 50);
	pLifeSprite->SetPosition(30, 30);

	SubmitDrawRegistration();
	SubmitUpdateRegistration();
}

HudTest::~HudTest()
{
	delete pLifeSprite;
}

void HudTest::Update()
{
	

}

void HudTest::Draw2D()
{
	pLifeSprite->Render(SceneManager::GetCurrentScene()->GetCameraManager()->GetCurrent2DCamera());
}
