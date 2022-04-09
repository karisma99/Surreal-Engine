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

};

#endif __SurrealAttorney