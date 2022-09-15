// ModelManager.h

#ifndef _ModelManager
#define _ModelManager

#include <Map>
#include "Surreal Graphics/GraphicsCore.h"

class ModelManager
{
	friend class ModelManagerAttorney;

private:

	static ModelManager* ptrInstance;

	ModelManager();
	ModelManager(const ModelManager& c) = delete;
	ModelManager& operator = (const ModelManager& t) = delete;
	~ModelManager() = default;

	static ModelManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ModelManager;
		return *ptrInstance;
	};

	std::string DefaultPath = "../Assets/Models/";
	std::map<std::string, Model*> ModelStorage;

public:
	static void Load(const std::string& key, const std::string& path) { Instance().privLoad(key, path); };
	static void Load(const std::string& key, const Model::PreMadeModels pmm) { Instance().privLoad(key, pmm); };
	static Model* Get(const std::string key) { return Instance().privGet(key); };

private:
	static void Delete() { Instance().privDelete(); };

	void privLoad(const std::string& key, const std::string& path);
	void privLoad(const std::string& key, const Model::PreMadeModels pmm);
	Model* privGet(const std::string& key);
	void privDelete();

};

#endif _ModelManager