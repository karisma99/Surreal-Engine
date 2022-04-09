//Model Manager

#include "ModelManager.h"

ModelManager* ModelManager::ptrInstance = nullptr;

ModelManager::ModelManager()
{

}

void ModelManager::privLoad(const std::string& key, const std::string& path)
{
	assert(ModelStorage.find(key) == ModelStorage.end());

	std::string ExpectedPath = DefaultPath + path;
	Model* pModel = new Model(&ExpectedPath[0]);
	ModelStorage.insert({ key, pModel });
}

void ModelManager::privLoad(const std::string& key, const Model::PreMadeModels pmm)
{
	assert(ModelStorage.find(key) == ModelStorage.end());

	Model* pModel = new Model(pmm);
	ModelStorage.insert({ key, pModel });
}

Model* ModelManager::privGet(const std::string& key)
{
	auto it = ModelStorage.find(key);

	assert(it != ModelStorage.end());

	return it->second;
}

void ModelManager::privDelete()
{
	for (auto& it : ModelStorage)
	{
		delete it.second;
	}

	ModelStorage.clear();

	delete ptrInstance;

}

