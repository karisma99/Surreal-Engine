//Scene

#include "Scene.h"
#include "AlarmableAttorney.h"
#include "DrawableAttorney.h"
#include "UpdateableAttorney.h"
#include "InputableAttorney.h"

Scene::Scene()
{
	UpdateMgr = new UpdateableManager();
	DrawMgr = new DrawableManager();
	AlarmMgr = new AlarmableManager();
	InputMgr = new KeyboardEventManager();
	CollideMgr = new CollidableManager();
	pRegistrationBroker = new SceneRegistrationBroker();

	CameraMgr = new CameraManager();
}

Scene::~Scene()
{
	delete UpdateMgr;
	UpdateMgr = nullptr;

	delete DrawMgr;
	DrawMgr = nullptr;

	delete AlarmMgr; 
	AlarmMgr = nullptr; 

	delete InputMgr; 
	InputMgr = nullptr;

	delete CollideMgr;
	CollideMgr = nullptr;

	delete pRegistrationBroker; 
	pRegistrationBroker = nullptr;

	delete CameraMgr; 
	CameraMgr = nullptr;
}

void Scene::Initialize()
{
	
}

void Scene::SceneEnd()
{

}

void Scene::Update()
{
	pRegistrationBroker->ExecuteCommands();
	InputMgr->ProcessKeys();
	UpdateMgr->ProcessElements();
	CollideMgr->ProcessCollisions();
	AlarmMgr->ProcessAlarms();
}

void Scene::Draw()
{
	DrawMgr->ProcessElements();
}


void Scene::Register(Updateable* up, UpdateableManager::StorageListRef ref)
{
	UpdateableManager::StorageListRef r = UpdateMgr->Register(up, ref);
	UpdateableAttorney::theScene::SetDeleteRef(up, r);
}

void Scene::Deregister(UpdateableManager::StorageListRef ref)
{
	UpdateMgr->Deregister(ref);
}

void Scene::Register(Drawable* up, DrawableManager::StorageListRef ref)
{
	DrawableManager::StorageListRef r = DrawMgr->Register(up, ref);
	DrawableAttorney::theScene::SetDeleteRef(up, r);
}

void Scene::Deregister(DrawableManager::StorageListRef ref)
{
	DrawMgr->Deregister(ref);
}

void Scene::Register(Alarmable* up, AlarmableManager::AlarmID id, float t, AlarmableManager::StorageListRef ref)
{
	AlarmableManager::StorageListRef r = AlarmMgr->Register(up, id, t, ref);
	AlarmableAttorney::theScene::SetDeleteRef(up, id, r);
}

void Scene::Deregister(AlarmableManager::StorageListRef ref)
{
	AlarmMgr->Deregister(ref);
}

void Scene::Register(Inputable* up, AZUL_KEY k, EventType e,
	KeyboardEventManager::StorageListRef KBref, SingleKeyEventManager::InputableCollectionRef Sref)
{
	KeyboardEventManager::StorageListRef r = InputMgr->Register(up, k, e);
	InputableAttorney::DeleteRef::SetKBDeleteRef(up, k, e, r);
}

void Scene::Deregister(EventType e, KeyboardEventManager::StorageListRef KBref, SingleKeyEventManager::InputableCollectionRef Sref)
{
	InputMgr->Deregister(e, KBref, Sref);
}

void Scene::SubmittCommand(CommandBase* cmd)
{
	pRegistrationBroker->AddCommand(cmd);
}

CameraManager* Scene::GetCameraManager()
{
	return CameraMgr;
}


