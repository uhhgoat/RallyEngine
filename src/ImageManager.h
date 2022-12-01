#pragma once
#include <map>
#include <string>
#include "Texture.h"
#include "AzulCore.h"

class ImageManager
{
private:
	friend class Rally;
	static ImageManager* ptrInstance;

	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;
	~ImageManager();

	//const std::string DefaultPath = "Textures/";

	std::map<std::string, Image*> myMap;

	static ImageManager& Instance()
	{
		if (!ptrInstance)
			ptrInstance = new ImageManager;
		return *ptrInstance;
	};

	Image* privGet(std::string key);
	Image* privLoad(std::string key, Texture* tex);
	Image* privLoad(std::string key, Texture* tex, Rect* r);

	static void Delete();
public:

	static Image* Get(std::string key) { return Instance().privGet(key); };

	static Image* Load(std::string key, Texture* tex) { return Instance().privLoad(key, tex); };
	static Image* Load(std::string key, Texture* tex, Rect* r) { return Instance().privLoad(key, tex, r); };

};
