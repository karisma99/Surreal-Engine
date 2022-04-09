// ScreenLogAttorney

#ifndef _ScreenLogAttorney
#define _ScreenLogAttorney

#include "ScreenLog.h"

class ScreenLogAttorney
{
	friend class Surreal;

private:
	static void Delete() { ScreenLog::Delete(); };
	static void Render() { ScreenLog::Render(); };
};

#endif _ScreenLogAttorney