#include "SpriteFontManager.h"
#include <stdexcept>
#include "M_Assert.h"

SpriteFontManager* SpriteFontManager::ptrInstance = nullptr;


void SpriteFontManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


SpriteFontManager::~SpriteFontManager()
{
	//delete all entities.
	for (std::map<std::string, SpriteFont*>::iterator it = myMap.begin(); it != myMap.end(); it++)
	{
		delete it->second;
	}
}
SpriteFont* SpriteFontManager::privGet(std::string key)
{
	// test for non existing key
	std::string errmsg = "Key \'" + key + "\' does not exists";
	M_Assert(myMap[key] != nullptr, errmsg.c_str());
	return myMap[key];
}

void SpriteFontManager::privLoad(std::string key, std::string path)
{
	//test for used key
	std::string errmsg = "Key \'" + key + "\' already exists";
	M_Assert(myMap[key] == nullptr, errmsg.c_str());
	myMap[key] = new SpriteFont(key, path);
}