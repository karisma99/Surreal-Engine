#ifndef _KeyboardEventManager
#define _KeyboardEventManager

#include <map>
#include "EventType.h"
#include "SingleKeyEventManager.h"
#include "Keyboard.h"

class Inputable;

class KeyboardEventManager
{
private:
	using MapKeyManager = std::map<SURREAL_KEY, SingleKeyEventManager*>;
	MapKeyManager mapSKMgrs;

public:
	using StorageListRef = MapKeyManager::iterator;
	static const int NumKeys = 101; 

	KeyboardEventManager() = default;
	KeyboardEventManager(const KeyboardEventManager& c) = delete;
	KeyboardEventManager& operator = (const KeyboardEventManager& t) = delete;
	~KeyboardEventManager();

	void ProcessKeys();

	StorageListRef Register(Inputable* up, SURREAL_KEY k, EventType e);
	void Deregister(EventType e, StorageListRef ref, SingleKeyEventManager::InputableCollectionRef SingleRef);

};

#endif _KeyboardEventManager