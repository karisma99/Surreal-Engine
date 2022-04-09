//SceneManager

#include "SceneManager.h"
#include "SceneAttorney.h"
#include "SceneNull.h"

SceneManager* SceneManager::ptrInstance = nullptr;

SceneManager::SceneManager()
{
	pCurrentScene = new SceneNull();
	pNullCmd = new SceneChangeNullCommand(); 
	pChangeCmd = new SceneChangeCommand();
	pChangeSceneCmd = pNullCmd;

}

void SceneManager::privDelete()
{
	SceneAttorney::GameLoop::SceneEnd(pCurrentScene);

	delete pCurrentScene;
	pCurrentScene = nullptr;

	delete pNullCmd;
	pNullCmd = nullptr; 

	delete pChangeCmd;
	pChangeCmd = nullptr; 

	delete ptrInstance;
	ptrInstance = nullptr;

}

void SceneManager::privStartScene()
{
	SceneAttorney::GameLoop::Initialize(pCurrentScene);
}

void SceneManager::privSetNextScene(Scene* pNewScene)
{
	assert(pNewScene != pCurrentScene);
	
	pChangeCmd->SetScene(pNewScene); 
	pChangeSceneCmd = pChangeCmd;
}

void SceneManager::privChangeScene(Scene* ns)
{
	SceneAttorney::GameLoop::SceneEnd(pCurrentScene);
	delete pCurrentScene; 
	pCurrentScene = ns; 
	pChangeSceneCmd = pNullCmd;
	privStartScene();
}


Scene* SceneManager::privGetCurrentScene()
{
	return pCurrentScene;
}

void SceneManager::privUpdate()
{
	pChangeSceneCmd->Execute();

	SceneAttorney::GameLoop::Update(pCurrentScene);
}

void SceneManager::privDraw()
{
	SceneAttorney::GameLoop::Draw(pCurrentScene);
}
