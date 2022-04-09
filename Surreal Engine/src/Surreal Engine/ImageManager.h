// ImageManager

#ifndef _ImageManager
#define _ImageManager

#include "Image.h"
#include <map>

class Image;
class Texture;

class ImageManager
{
	friend class ImageManagerAttorney;

private:

	static ImageManager* ptrInstance;

	ImageManager();
	ImageManager(const ImageManager& c) = delete;
	ImageManager& operator = (const ImageManager& t) = delete;
	~ImageManager() = default;

	static ImageManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ImageManager;
		return *ptrInstance;
	};

	std::string DefaultPath = "Images/";
	std::map<std::string, Image*> StorageMap;

public:
	static void Load(const std::string& key, Texture* tex) { Instance().privLoad(key, tex); };
	static void Load(const std::string& key, Texture* tex, Rect* r) { Instance().privLoad(key, tex, r); };
	static Image* Get(const std::string key) { return Instance().privGet(key); };

private:
	static void Delete() { Instance().privDelete(); };

	void privLoad(const std::string& key, Texture* tex);
	void privLoad(const std::string& key, Texture* tex, Rect* r);
	Image* privGet(const std::string& key);
	void privDelete();

};

#endif _ImageManager