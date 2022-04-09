//Shader Manager

#include "ShaderManager.h"
#include "ShaderObject.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;

ShaderManager::ShaderManager()
{

}

void ShaderManager::privLoad(const std::string& key, const std::string& path)
{

	assert(ShaderStorage.find(key) == ShaderStorage.end());

	std::string ExpectedPath = DefaultPath + path; 
	ShaderObject* pShader = new ShaderObject(&ExpectedPath[0]);
	ShaderStorage.insert({ key, pShader });
}

void ShaderManager::privLoadDefaultShaders()
{
	std::string ExpectedPath = DefaultPath + "spriteRender";
	ShaderObject* pShader = new ShaderObject(&ExpectedPath[0]);
	ShaderStorage.insert({ "spriteRender", pShader });
}

ShaderObject* ShaderManager::privGet(const std::string& key)
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

