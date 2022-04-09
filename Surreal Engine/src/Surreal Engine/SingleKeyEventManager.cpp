// SingleKeyEventManager

#include "SingleKeyEventManager.h"
#include "InputableAttorney.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
{
	key = k;
}

void SingleKeyEventManager::ProcessKeyEvent()
{
	if (Keyboard::GetKeyState(key) && !wasPressed)
	{	//Was not pressed but now is
		for (auto& it : keyPressCol)
		{
			Inputable* up = it;
			InputableAttorney::GameLoop::KeyPressed(up, key);
		}

		wasPressed = true; 
	}
	else if (!Keyboard::GetKeyState(key) && wasPressed)
	{	//Was Pressed but now is released
		for (auto& it: keyReleaseCol)
		{
			Inputable* up = it; 
			InputableAttorney::GameLoop::KeyReleased(up, key);
		}

		wasPressed = false;
	}
}

SingleKeyEventManager::InputableCollectionRef SingleKeyEventManager::Register(Inputable* p, EventType e)
{
	InputableCollectionRef ref; 

	if (e == EventType::KEY_PRESS)
	{
		ref = keyPressCol.insert(keyPressCol.end(), p);
	}
	else
	{
		ref = keyReleaseCol.insert(keyReleaseCol.end(), p);
	}

	return ref;
}

void SingleKeyEventManager::Deregister(EventType e, SingleKeyEventManager::InputableCollectionRef ref)
{
	if (e == EventType::KEY_PRESS)
	{
		keyPressCol.erase(ref);
	}
	else
	{
		keyReleaseCol.erase(ref);
	}
}