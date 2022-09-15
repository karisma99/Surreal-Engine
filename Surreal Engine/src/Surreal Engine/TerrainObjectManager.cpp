//TerrainObjectManager

#include "TerrainObjectManager.h"
#include "TerrainObject.h"

TerrainObjectManager* TerrainObjectManager::ptrInstance = nullptr;

TerrainObjectManager::TerrainObjectManager()
{

}

void TerrainObjectManager::privLoad(const std::string& key, const char* heightmapFile, const std::string& textureKey, float len, 
	float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	assert(TerrainObjectStorage.find(key) == TerrainObjectStorage.end());

	std::string heightmapPath = DefaultPath + heightmapFile;
	TerrainObject* pterrain = new TerrainObject(heightmapPath, textureKey, len, maxheight, ytrans, RepeatU, RepeatV);
	TerrainObjectStorage.insert({ key, pterrain });
}

TerrainObject* TerrainObjectManager::privGet(const std::string& key)
{
	auto it = TerrainObjectStorage.find(key);

	assert(it != TerrainObjectStorage.end());

	return it->second;
}

void TerrainObjectManager::privDelete()
{
	for (auto& it : TerrainObjectStorage)
	{
		delete it.second;
	}

	TerrainObjectStorage.clear();

	delete ptrInstance;

}

