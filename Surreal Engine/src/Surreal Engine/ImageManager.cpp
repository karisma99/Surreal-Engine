//ImageManager

#include "ImageManager.h"

ImageManager* ImageManager::ptrInstance = nullptr;

ImageManager::ImageManager()
{

}

void ImageManager::privLoad(const std::string& key, Texture* tex)
{
	assert(StorageMap.find(key) == StorageMap.end());

	StorageMap.insert(std::pair<std::string, Image*>(key, new Image(tex, new Rect(0.0f, 0.0f, (float)tex->GetWidth(), (float)tex->GetHeight()))));
}

void ImageManager::privLoad(const std::string& key, Texture* tex, Rect* r)
{
	assert(StorageMap.find(key) == StorageMap.end());

	StorageMap.insert(std::pair<std::string, Image*>(key, new Image(tex, r)));
}

Image* ImageManager::privGet(const std::string& key)
{
	auto it = StorageMap.find(key);

	assert(it != StorageMap.end());

	return it->second;
}

void ImageManager::privDelete()
{
	for (auto& it : StorageMap)
	{
		delete it.second;
	}

	StorageMap.clear();

	delete ptrInstance;

}

