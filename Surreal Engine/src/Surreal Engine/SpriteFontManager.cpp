//SpriteFontManager

#include "SpriteFontManager.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;

SpriteFontManager::SpriteFontManager()
{

}

void SpriteFontManager::privLoad(const std::string& key, const std::string path)
{

	assert(SpriteFontStorage.find(key) == SpriteFontStorage.end());

	std::string ExpectedPath = DefaultPath + path;
	SpriteFont* pFont = new SpriteFont(&ExpectedPath[0]);
	SpriteFontStorage.insert({ key, pFont });
}

SpriteFont* SpriteFontManager::privGet(const std::string& key)
{
	auto it = SpriteFontStorage.find(key);

	assert(it != SpriteFontStorage.end());

	return it->second;
}

void SpriteFontManager::privDelete()
{
	for (auto& it : SpriteFontStorage)
	{
		delete it.second;
	}

	SpriteFontStorage.clear();

	delete ptrInstance;

}

