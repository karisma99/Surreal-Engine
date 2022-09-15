// TerrainObjectManager.h

#ifndef _TerrainObjectManager
#define _TerrainObjectManager

#include <Map>
#include "Surreal Graphics/GraphicsCore.h"

class TerrainObject;

class TerrainObjectManager
{
	friend class TerrainObjectManagerAttorney;

private:

	static TerrainObjectManager* ptrInstance;

	TerrainObjectManager();
	TerrainObjectManager(const TerrainObjectManager& c) = delete;
	TerrainObjectManager& operator = (const TerrainObjectManager& t) = delete;
	~TerrainObjectManager() = default;

	static TerrainObjectManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TerrainObjectManager;
		return *ptrInstance;
	};

	std::string DefaultPath = "../Assets/Textures/";
	std::map<std::string, TerrainObject*> TerrainObjectStorage;

public:
	static void Load(const std::string& key, const char* heightmapFile, const std::string& textureKey, float len, 
		float maxheight, float ytrans, int RepeatU, int RepeatV) 
	{ Instance().privLoad(key, heightmapFile, textureKey, len, maxheight, ytrans, RepeatU, RepeatV); };
	static TerrainObject* Get(const std::string key) { return Instance().privGet(key); };

private:
	static void Delete() { Instance().privDelete(); };

	void privLoad(const std::string& key, const char* heightmapFile, const std::string& textureKey, float len, 
		float maxheight, float ytrans, int RepeatU, int RepeatV);
	TerrainObject* privGet(const std::string& key);
	void privDelete();

};

#endif _TerrainObjectManager