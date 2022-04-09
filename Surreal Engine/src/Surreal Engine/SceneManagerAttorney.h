// SceneManagerAttorney.h

#ifndef _SceneManagerAttorney
#define _SceneManagerAttorney

#include "SceneManager.h"

class SceneManagerAttorney
{
public:
	class GameLoop
	{
		friend class Surreal;

	private:
		static void StartScene() { SceneManager::StartScene(); }
		static void Delete() { SceneManager::Delete(); }

		static void Update() { SceneManager::Update(); }
		static void Draw() { SceneManager::Draw(); }
	};
	
public:
	class Command
	{
		friend class SceneChangeCommand; 

	private:
		static void ChangeScene(Scene* s) { SceneManager::ChangeScene(s); }
	};

};

#endif _SceneManagerAttorney