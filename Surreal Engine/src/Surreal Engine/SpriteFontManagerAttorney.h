// SpriteFontManagerAttorney.h

#ifndef _SpriteFontManagerAttorney
#define _SpriteFontManagerAttorney

#include "SpriteFontManager.h"

class SpriteFontManagerAttorney
{
	friend class Surreal;

private:
	static void Delete() { SpriteFontManager::Delete(); }
};

#endif _SpriteFontManagerAttorney