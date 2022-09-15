// TerrainObjectManagerAttorney.h

#ifndef _TerrainObjectManagerAttorney
#define _TerrainObjectManagerAttorney

#include "TerrainObjectManager.h"

class TerrainObjectManagerAttorney
{
	friend class Surreal;

private:
	static void Delete() { TerrainObjectManager::Delete(); }
};

#endif _TerrainObjectManagerAttorney