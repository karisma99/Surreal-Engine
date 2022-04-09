#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include <list>
#include "AzulCore.h"
#include "EventType.h"

class Inputable;

class SingleKeyEventManager
{
private:
	using InputableCollection = std::list<Inputable*>;
	InputableCollection keyPressCol;
	InputableCollection keyReleaseCol;

	AZUL_KEY key;

	bool wasPressed = false;

public:
	using InputableCollectionRef = InputableCollection::iterator;

	SingleKeyEventManager() = default;
	SingleKeyEventManager(AZUL_KEY k);
	SingleKeyEventManager(const SingleKeyEventManager& c) = delete;
	SingleKeyEventManager& operator = (const SingleKeyEventManager& t) = delete;
	~SingleKeyEventManager() = default;

	void ProcessKeyEvent();

	InputableCollectionRef Register(Inputable* up, EventType e);
	void Deregister(EventType e, InputableCollectionRef ref);

};

#endif _SingleKeyEventManager