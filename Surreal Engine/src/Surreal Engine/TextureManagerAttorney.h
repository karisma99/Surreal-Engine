// TextureManagerAttorney.h

#ifndef _TextureManagerAttorney
#define _TextureManagerAttorney

#include "TextureManager.h"

class TextureManagerAttorney
{
	friend class Surreal;

private:
	static void Delete() { TextureManager::Delete(); }
};

#endif _TextureManagerAttorney