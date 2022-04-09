// UpdateableAttorney.h

#ifndef _UpdateableAttorney
#define _UpdateableAttorney

#include "Updateable.h"

class UpdateableAttorney
{
public:
	class GameLoop
	{
		friend class UpdateableManager;

	private:
		static void Update(Updateable* p) { p->Update(); }
	};

public: 
	class Registration
	{
		friend class UpdateRegistrationCommand; 
		friend class UpdateDeregistrationCommand; 

	private:
		static void SceneRegistration(Updateable* p) { p->SceneRegistration(); }
		static void SceneDeregistration(Updateable* p) { p->SceneDegregistration(); }
	};

public:
	class theScene
	{
		friend class Scene; 
	private:
		static void SetDeleteRef(Updateable* p, UpdateableManager::StorageListRef ref) { p->pMyDeleteRef = ref; }
	};
};

#endif _UpdateableAttorney