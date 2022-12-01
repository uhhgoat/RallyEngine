#include "ImageManager.h"

ImageManager* ImageManager::ptrInstance = nullptr;


void ImageManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


ImageManager::~ImageManager()
{
	//delete all entities.
	for (std::map<std::string, Image*>::iterator it = myMap.begin(); it != myMap.end(); it++)
	{
		delete it->second;
	}
}
Image* ImageManager::privGet(std::string key)
{
	return myMap[key];
}

Image* ImageManager::privLoad(std::string key, Texture* tex)
{
	return myMap[key] = new Image(tex, new Rect(0.0f, 0.0f, (float)(tex->getWidth()), (float)(tex->getHeight())));
}
Image* ImageManager::privLoad(std::string key, Texture* tex, Rect* r)
{
	return myMap[key] = new Image(tex, r);
}