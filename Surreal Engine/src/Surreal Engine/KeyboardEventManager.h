#ifndef _KeyboardEventManager
#define _KeyboardEventManager

#include <map>
#include "AzulCore.h"
#include "EventType.h"
#include "SingleKeyEventManager.h"

class Inputable;

class KeyboardEventManager
{
private:
	using MapKeyManager = std::map<AZUL_KEY, SingleKeyEventManager*>;
	MapKeyManager mapSKMgrs;

public:
	using StorageListRef = MapKeyManager::iterator;
	static const int NumKeys = 101; 

	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager& c) = delete;
	KeyboardEventManager& operator = (const KeyboardEventManager& t) = delete;
	~KeyboardEventManager();

	void ProcessKeys();

	StorageListRef Register(Inputable* up, AZUL_KEY k, EventType e);
	void Deregister(EventType e, StorageListRef ref, SingleKeyEventManager::InputableCollectionRef SingleRef);

};

#endif _KeyboardEventManager