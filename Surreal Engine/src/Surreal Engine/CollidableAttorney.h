// CollidableAttorney

#ifndef _CollidableAttorney
#define _CollidableAttorney

#include "Collidable.h"

class CollidableAttorney
{
public:
	class Registration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeregistrationCommand;

	private:
		static void SceneRegistration(Collidable* p) { p->SceneRegistration(); }
		static void SceneDeregistration(Collidable* p) { p->SceneDegregistration(); }
	}; 

//public:
//	class theScene
//	{
//		friend class Scene;
//	private:
//		static void SetDeleteRef(Drawable* p, DrawableManager::StorageListRef ref) { p->pMyDeleteRef = ref; }
//	};
};

#endif _CollidableAttorney