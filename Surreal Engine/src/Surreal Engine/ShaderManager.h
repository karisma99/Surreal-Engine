// ShaderManager.h

#ifndef _ShaderManager
#define _ShaderManager

#include <map>

class ShaderObject;

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

	std::string DefaultPath = "Shaders/";
	std::map<std::string, ShaderObject*> ShaderStorage; 

public:
	static void Load(const std::string& key, const std::string& path) { Instance().privLoad(key, path); };
	static ShaderObject* Get(const std::string key) { return Instance().privGet(key); };

private:
	static void Delete() { Instance().privDelete(); };
	static void LoadDefaultShaders() { Instance().privLoadDefaultShaders(); };

	void privLoad(const std::string& key, const std::string& path); 
	ShaderObject* privGet(const std::string& key); 
	void privDelete();
	void privLoadDefaultShaders();

};

#endif _ShaderManager