// DrawableAttorney

#ifndef _DrawableAttorney
#define _DrawableAttorney

#include "Drawable.h"

class DrawableAttorney
{
public:
	class GameLoop
	{
		friend class DrawableManager;

	private:
		static void Draw(Drawable* p) { p->Draw(); }
		static void Draw2D(Drawable* p) { p->Draw2D(); }
	};

public:
	class Registration
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;

	private:
		static void SceneRegistration(Drawable* p) { p->SceneRegistration(); }
		static void SceneDeregistration(Drawable* p) { p->SceneDegregistration(); }
	};

public: 
	class theScene
	{
		friend class Scene;
	private:
		static void SetDeleteRef(Drawable* p, DrawableManager::StorageListRef ref) { p->pMyDeleteRef = ref; }
	};
};

#endif _DrawableAttorney