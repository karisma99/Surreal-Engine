// TextureManager.h

#ifndef _TextureManager
#define _TextureManager

#include <map>

class Texture;

class TextureManager
{
	friend class TextureManagerAttorney;

private:

	static TextureManager* ptrInstance;

	TextureManager();
	TextureManager(const TextureManager& c) = delete;
	TextureManager& operator = (const TextureManager& t) = delete;
	~TextureManager() = default;

	static TextureManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TextureManager;
		return *ptrInstance;
	};

	std::string DefaultPath = "Textures/";
	std::map<std::string, Texture*> TextureStorage;

public:
	static void Load(const std::string& key, const std::string& path) { Instance().privLoad(key, path); };
	static void Load(const std::string& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char alpha = 255U) { Instance().privLoad(key, red, green, blue, alpha); };
	static Texture* Get(const std::string key) { return Instance().privGet(key); };

private:
	static void Delete() { Instance().privDelete(); };

	void privLoad(const std::string& key, const std::string& path);
	void privLoad(const std::string& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char alpha);
	Texture* privGet(const std::string& key);
	void privDelete();

};

#endif _TextureManager