#ifndef _Scene
#define _Scene

#include "UpdateableManager.h"
#include "DrawableManager.h"
#include "AlarmableManager.h"
#include "CollidableManager.h"
#include "Inputable.h"
#include "CommandBase.h"
#include "SceneRegistrationBroker.h"
#include "CameraManager.h"

class Updateable;
class Drawable;
class Alarmable;
class Inputable;
class Collidable;
class UpdateableManager;
class DrawableManager;
class AlarmableManager;
class InputableManager;
class CollidableManager;

class Scene
{
	friend class SceneAttorney;
private:
	
	void Register(Updateable* p, UpdateableManager::StorageListRef ref);
	void Register(Drawable* p, DrawableManager::StorageListRef ref);
	void Register(Alarmable* p, AlarmableManager::AlarmID id, float t, AlarmableManager::StorageListRef ref);
	void Register(Inputable* p, AZUL_KEY k, EventType e, KeyboardEventManager::StorageListRef KBref,
		SingleKeyEventManager::InputableCollectionRef Sref);
	void Deregister(DrawableManager::StorageListRef ref);
	void Deregister(UpdateableManager::StorageListRef ref);
	void Deregister(AlarmableManager::StorageListRef ref);
	void Deregister(EventType e, KeyboardEventManager::StorageListRef KBref, SingleKeyEventManager::InputableCollectionRef Sref);
	void SubmittCommand(CommandBase* cmd);

	virtual void Initialize();
	virtual void SceneEnd();
	virtual void Update();
	virtual void Draw();

	UpdateableManager* UpdateMgr; 
	DrawableManager* DrawMgr; 
	AlarmableManager* AlarmMgr;
	KeyboardEventManager* InputMgr;
	CollidableManager* CollideMgr;
	SceneRegistrationBroker* pRegistrationBroker;
	CameraManager* CameraMgr;

public: 
	Scene();
	Scene(const Scene& c) = delete;
	Scene& operator = (const Scene& t) = delete;
	~Scene();

	CameraManager* GetCameraManager();

	template<typename C1> 
	void SetCollisionSelf()
	{
		CollideMgr->SetCollisionSelf<C1>();
	}

	template<typename C1, typename C2>
	void SetCollisionPair()
	{
		CollideMgr->SetCollisionPair<C1, C2>();
	}
	
};

#endif _Scene