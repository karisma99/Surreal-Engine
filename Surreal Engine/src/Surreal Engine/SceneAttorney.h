// SceneManagerAttorney.h

#ifndef _SceneAttorney
#define _SceneAttorney

#include "Scene.h"
#include "AzulCore.h"
#include "EventType.h"
#include "SceneManager.h"

class SceneAttorney
{
public:
	class GameLoop
	{
		friend class SceneManager;

	private:
		static void Initialize(Scene* s) { s->Initialize(); }
		static void SceneEnd(Scene* s) { s->SceneEnd(); }
		static void Update(Scene* s) { s->Update(); }
		static void Draw(Scene* s) { s->Draw(); }
	};

public:
	class UpdateableReg
	{
		friend class Updateable; 
	private:
		static void Register(Scene* s, Updateable* p, UpdateableManager::StorageListRef ref) {
			s->Register(p, ref); }

		static void Deregister(Scene* s, UpdateableManager::StorageListRef ref) {
			s->Deregister(ref); }

		static void SubmittCommand(Scene* s, CommandBase* cmd) {
			s->SubmittCommand(cmd); }
	};

public:
	class DrawableReg
	{
		friend class Drawable;
	private:
		static void Register(Scene* s, Drawable* p, DrawableManager::StorageListRef ref) {
			s->Register(p, ref);
		}

		static void Deregister(Scene* s, DrawableManager::StorageListRef ref) {
			s->Deregister(ref);
		}

		static void SubmittCommand(Scene* s, CommandBase* cmd) {
			s->SubmittCommand(cmd);
		}
	};

public:
	class AlarmableReg
	{
		friend class Alarmable;
	private:
		static void Register(Scene* s, Alarmable* p, AlarmableManager::AlarmID id, float t, AlarmableManager::StorageListRef ref) {
			s->Register(p, id, t, ref);
		}

		static void Deregister(Scene* s, AlarmableManager::StorageListRef ref) {
			s->Deregister(ref);
		}

		static void SubmittCommand(Scene* s, CommandBase* cmd) {
			s->SubmittCommand(cmd);
		}
	};

public:
	class InputableReg
	{
		friend class Inputable;
	private:
		static void Register(Scene* s, Inputable* p, AZUL_KEY k, EventType e, 
			KeyboardEventManager::StorageListRef KBref, SingleKeyEventManager::InputableCollectionRef Sref) {
			s->Register(p, k, e, KBref, Sref);
		}

		static void Deregister(Scene* s, EventType e, KeyboardEventManager::StorageListRef KBref, SingleKeyEventManager::InputableCollectionRef Sref) {
			s->Deregister(e, KBref, Sref);
		}

		static void SubmittCommand(Scene* s, CommandBase* cmd) {
			s->SubmittCommand(cmd);
		}
	};

public:
	class CollidableReg
	{
		friend class Collidable; 
	private:
		static CollidableManager* GetCollisionMgr() { return SceneManager::GetCurrentScene()->CollideMgr; };

		static void SubmittCommand(Scene* s, CommandBase* cmd) {
			s->SubmittCommand(cmd);
		}
	};

public:
	class GameObjectReg
	{
		friend class GameObject;
	private:
		static void SubmittCommand(Scene* s, CommandBase* cmd) {
			s->SubmittCommand(cmd);
		}
	};
};

#endif _SceneManagerAttorney