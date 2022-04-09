// ShaderManagerAttorney.h

#ifndef _ShaderManagerAttorney
#define _ShaderManagerAttorney

#include "ShaderManager.h"

class ShaderManagerAttorney
{
	friend class Surreal;

private:
	static void Delete() { ShaderManager::Delete(); }
	static void LoadDefaultShaders() { ShaderManager::LoadDefaultShaders(); }
};

#endif _ShaderManagerAttorney