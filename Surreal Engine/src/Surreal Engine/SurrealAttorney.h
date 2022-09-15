// SurrealAttorney.h

#ifndef __SurrealAttorney
#define _SurrealAttorney

#include "Surreal.h"

class SurrealAttorney
{
public:
	class Time
	{
		friend class FreezeTime;
		friend class TimeManager;

	private:
		static float GetTime() { return Surreal::GetTime(); }
	};

public:
	class GameLoop
	{
		friend class WindowController;

	private:
		static void Initialize(HWND hwnd) { Surreal::Initialize(hwnd); }
		static void Update() { Surreal::Update(); }
		static void Draw() { Surreal::Draw(); }
		static void Delete() { Surreal::Delete(); }
		static void UnloadContent() { Surreal::UnLoadContent(); }

	};

};

#endif __SurrealAttorney