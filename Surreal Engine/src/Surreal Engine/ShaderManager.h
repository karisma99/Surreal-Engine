// ShaderManager.h

#ifndef _ShaderManager
#define _ShaderManager

#include <map>
#include "Surreal Graphics/GraphicsCore.h"

class ShaderManager
{
	friend class ShaderManagerAttorney; 

private:

	static ShaderManager* ptrInstance;

	ShaderManager();
	ShaderManager(const ShaderManager& c) = delete;
	ShaderManager& operator = (const ShaderManager& t) = delete;
	~ShaderManager() = default;

	static ShaderManager& Instance() 
	{
		if (!ptrInstance)
			ptrInstance = new ShaderManager;
		return *ptrInstance;
	};

	std::string DefaultPath = "../Assets/Shaders/";
	std::map<std::string, ShaderBase*> ShaderStorage; 

public:
	static void Load(const std::string& key, ShaderBase* pShader) { Instance().privLoad(key, pShader); };
	static ShaderBase* Get(const std::string key) { return Instance().privGet(key); };

private:
	static void Delete() { Instance().privDelete(); };

	void privLoad(const std::string& key, ShaderBase* pShader); 
	ShaderBase* privGet(const std::string& key); 
	void privDelete();

};

#endif _ShaderManager