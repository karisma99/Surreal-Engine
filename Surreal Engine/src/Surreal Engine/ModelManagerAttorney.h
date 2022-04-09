// ModelManagerAttorney.h

#ifndef _ModelManagerAttorney
#define _ModelManagerAttorney

#include "ModelManager.h"

class ModelManagerAttorney
{
	friend class Surreal;

private:
	static void Delete() { ModelManager::Delete(); }
};

#endif _ModelManagerAttorney