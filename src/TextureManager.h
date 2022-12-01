#pragma once
#include <map>
#include <string>
#include "Texture.h"

class TextureManager
{
private:
	friend class Rally;
	static TextureManager* ptrInstance;

	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	~TextureManager();

	const std::string DefaultPath = "Textures/";

	std::map<std::string, Texture*> myMap;

	static TextureManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new TextureManager;
		return *ptrInstance;
	};
	Texture* privGet(std::string key);
	void privLoad(std::string key, std::string path);
	void privLoad(std::string key, const unsigned char& red, const unsigned char& green, const unsigned char& blue);

	static void Delete();
public:

	static Texture* Get(std::string key) { return Instance().privGet(key); };

	static void Load(std::string key, std::string path) { Instance().privLoad(key, path); };

	static void Load(std::string key, const unsigned char& red, const unsigned char& green, const unsigned char& blue) { Instance().privLoad(key, red, green, blue); };

};
