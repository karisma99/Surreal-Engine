//KeyboardEventManager

#include "KeyboardEventManager.h"
#include "InputableAttorney.h"

KeyboardEventManager::~KeyboardEventManager()
{
	for (auto& it : mapSKMgrs)
	{
		delete it.second; 
		it.second = nullptr;
	}
}

void KeyboardEventManager::ProcessKeys()
{
	for (auto& it : mapSKMgrs)
	{
		it.second->ProcessKeyEvent();
	}
}

KeyboardEventManager::StorageListRef KeyboardEventManager::Register(Inputable* p, AZUL_KEY k, EventType e)
{
	StorageListRef ref = mapSKMgrs.find(k);
	SingleKeyEventManager::InputableCollectionRef SingleRef;

	if (ref == mapSKMgrs.end())
	{ 
		SingleKeyEventManager* SKMgr = new SingleKeyEventManager(k); 
		SingleRef = SKMgr->Register(p, e);
		ref = mapSKMgrs.insert(mapSKMgrs.end(), std::pair<AZUL_KEY, SingleKeyEventManager*>(k, SKMgr));
	}
	else
	{
		SingleRef = ref->second->Register(p, e);
	}

	InputableAttorney::SingleDeleteRef::SetSDeleteRef(p, k , e, SingleRef);

	return ref;
}

void KeyboardEventManager::Deregister(EventType e, StorageListRef ref, SingleKeyEventManager::InputableCollectionRef SingleRef)
{
	ref->second->Deregister(e, SingleRef);
}