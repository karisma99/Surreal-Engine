#ifndef _SingleKeyEventManager
#define _SingleKeyEventManager

#include <list>
#include "EventType.h"
#include "Keyboard.h"

class Inputable;

class SingleKeyEventManager
{
private:
	using InputableCollection = std::list<Inputable*>;
	InputableCollection keyPressCol;
	InputableCollection keyReleaseCol;

	SURREAL_KEY key;

	bool wasPressed = false;

public:
	using InputableCollectionRef = InputableCollection::iterator;

	SingleKeyEventManager() = default;
	SingleKeyEventManager(SURREAL_KEY k);
	SingleKeyEventManager(const SingleKeyEventManager& c) = delete;
	SingleKeyEventManager& operator = (const SingleKeyEventManager& t) = delete;
	~SingleKeyEventManager() = default;

	void ProcessKeyEvent();

	InputableCollectionRef Register(Inputable* up, EventType e);
	void Deregister(EventType e, InputableCollectionRef ref);

};

#endif _SingleKeyEventManager