//Texture Manager

#include "TextureManager.h"
#include <codecvt>

TextureManager* TextureManager::ptrInstance = nullptr;

TextureManager::TextureManager()
{

}

void TextureManager::privLoad(const std::string& key, const std::string& path)
{

	assert(TextureStorage.find(key) == TextureStorage.end());

	std::wstring ExpectedPath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(DefaultPath + path);
	LPCWSTR myPath = ExpectedPath.c_str();
	Texture* pTexture = new Texture(myPath);
	TextureStorage.insert({ key, pTexture });
}

// How do we do this?
//void TextureManager::privLoad(const std::string& key, const unsigned char& red, const unsigned char& green, const unsigned char& blue, const unsigned char alpha)
//{
//	assert(TextureStorage.find(key) == TextureStorage.end());
//
//	Texture* pTexture = new Texture(red, green, blue, alpha);
//	TextureStorage.insert({ key, pTexture });
//}

Texture* TextureManager::privGet(const std::string& key)
{
	auto it = TextureStorage.find(key);

	assert(it != TextureStorage.end());

	return it->second;
}

void TextureManager::privDelete()
{
	for (auto& it : TextureStorage)
	{
		delete it.second;
	}

	TextureStorage.clear();

	delete ptrInstance;

}

