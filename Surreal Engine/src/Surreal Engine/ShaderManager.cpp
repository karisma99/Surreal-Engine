//Shader Manager

#include "ShaderManager.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;

ShaderManager::ShaderManager()
{

}

void ShaderManager::privLoad(const std::string& key, ShaderBase* pShader)
{

	assert(ShaderStorage.find(key) == ShaderStorage.end());

	ShaderStorage.insert({ key, pShader });
}

ShaderBase* ShaderManager::privGet(const std::string& key)
{
	auto it = ShaderStorage.find(key); 

	assert(it != ShaderStorage.end());

	return it->second;
}

void ShaderManager::privDelete()
{
	for (auto& it : ShaderStorage)
	{
		delete it.second;
	}

	ShaderStorage.clear();

	delete ptrInstance;

}

