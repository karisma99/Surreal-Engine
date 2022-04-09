// GameObjectAttorney.

#ifndef _GameObjectAttorney
#define _GameObjectAttorney

#include "GameObject.h"

class GameObjectAttorney
{
public:
	class Registration
	{
		friend class GameObjectEntryCommand;
		friend class GameObjectExitCommand;

	private:
		static void SceneRegistration(GameObject* p) { p->ConnectToScene(); }
		static void SceneDeregistration(GameObject* p) { p->DisconnectFromScene(); }
	};
};

#endif _GameObjectAttorney