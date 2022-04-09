// SceneManager.h

#ifndef _SceneManager
#define _SceneManager

#include "Scene.h"
#include "SceneChangeCommandBase.h"
#include "SceneChangeNullCommand.h"
#include "SceneChangeCommand.h"

class Scene;
class SceneChangeCommandBase;
class SceneChangeNullCommand;
class SceneChangeCommand;

class SceneManager
{
	friend class SceneManagerAttorney; 

private:

	static SceneManager* ptrInstance;

	SceneManager();
	SceneManager(const SceneManager& c) = delete;
	SceneManager& operator = (const SceneManager& t) = delete;
	~SceneManager() = default;

	static SceneManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SceneManager;
		return *ptrInstance;
	};

	Scene* pCurrentScene;


public:
	static void ChangeScene(Scene* pNewScene) { Instance().privChangeScene(pNewScene); };
	static Scene* GetCurrentScene() { return Instance().privGetCurrentScene(); };
	static void SetNextScene(Scene* ns) { Instance().privSetNextScene(ns); };
	
private:
	static void StartScene() { Instance().privStartScene(); };
	void privStartScene();

	static void Delete() { Instance().privDelete(); };
	void privDelete();
	
	static void Update() { Instance().privUpdate(); };
	void privUpdate();

	static void Draw() { Instance().privDraw(); };
	void privDraw();

	void privChangeScene(Scene* pNewScene);
	void privSetNextScene(Scene* pns);
	Scene* privGetCurrentScene();

	SceneChangeCommandBase* pChangeSceneCmd;
	SceneChangeCommand* pChangeCmd; 
	SceneChangeNullCommand* pNullCmd;
};

#endif _SceneManager