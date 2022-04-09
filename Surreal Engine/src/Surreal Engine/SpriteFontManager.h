// SpriteFontManager

#ifndef _SpriteFontManager
#define _SpriteFontManager

#include "SpriteFont.h"
#include <map>

class SpriteFont;

class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;

private:

	static SpriteFontManager* ptrInstance;

	SpriteFontManager();
	SpriteFontManager(const SpriteFontManager& c) = delete;
	SpriteFontManager& operator = (const SpriteFontManager& t) = delete;
	~SpriteFontManager() = default;

	static SpriteFontManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpriteFontManager;
		return *ptrInstance;
	};

	std::string DefaultPath = "Fonts/";
	std::map<std::string, SpriteFont*> SpriteFontStorage;

public:
	static void Load(const std::string& key, const std::string path) { Instance().privLoad(key, path); };
	static SpriteFont* Get(const std::string key) { return Instance().privGet(key); };

private:
	static void Delete() { Instance().privDelete(); };

	void privLoad(const std::string& key, const std::string path);
	SpriteFont* privGet(const std::string& key);
	void privDelete();

};

#endif _SpriteFontManager