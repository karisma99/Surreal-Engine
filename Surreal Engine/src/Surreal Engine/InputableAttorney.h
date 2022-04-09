// InputableAttorney

#ifndef _InputableAttorney
#define _InputableAttorney

#include "Inputable.h"

class InputableAttorney
{
public:
	class GameLoop
	{
		friend class SingleKeyEventManager;

	private:
		static void KeyPressed(Inputable* p, AZUL_KEY k) { p->KeyPressed(k); }
		static void KeyReleased(Inputable* p, AZUL_KEY k) { p->KeyReleased(k); }
	};

public:
	class Registration
	{
		friend class InputRegistrationCommand;
		friend class InputDeregistrationCommand;

	private:
		static void SceneRegistration(Inputable* p, AZUL_KEY k, EventType e) { p->InputRegistration(k, e); }
		static void SceneDeregistration(Inputable* p, AZUL_KEY k, EventType e) { p->InputDegregistration(k, e); }
	};

public:
	class DeleteRef
	{
		friend class Scene;
	private:
		static void SetKBDeleteRef(Inputable* p, AZUL_KEY k, EventType e, KeyboardEventManager::StorageListRef ref) { p->SetKeyboardDeleteRef(k, e, ref); }
	};

public:
	class SingleDeleteRef
	{
		friend class KeyboardEventManager;
	private:
		static void SetSDeleteRef(Inputable* p, AZUL_KEY k, EventType e, SingleKeyEventManager::InputableCollectionRef ref) { p->SetSingleDeleteRef(k, e, ref); }
	};
};

#endif _InputableAttorney
