// ImageManagerAttorney.h

#ifndef _ImageManagerAttorney
#define _ImageManagerAttorney

#include "ImageManager.h"

class ImageManagerAttorney
{
	friend class Surreal;

private:
	static void Delete() { ImageManager::Delete(); }
};

#endif _ImageManagerAttorney