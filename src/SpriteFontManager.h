#pragma once
#include <map>
#include <string>
#include "SpriteFont.h"
#include "SpriteFont.h"

class SpriteFontManager
{
private:
	friend class Rally;
	static SpriteFontManager* ptrInstance;

	SpriteFontManager() = default;
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager& operator=(const SpriteFontManager&) = delete;
	~SpriteFontManager();

	const std::string DefaultPath = "Fonts/";

	std::map<std::string, SpriteFont*> myMap;

	static SpriteFontManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new SpriteFontManager;
		return *ptrInstance;
	};
	SpriteFont* privGet(std::string key);
	void privLoad(std::string key, std::string path);

	static void Delete();
public:

	static SpriteFont* Get(std::string key) { return Instance().privGet(key); };

	static void Load(std::string key, std::string path) { Instance().privLoad(key, path); };

};
