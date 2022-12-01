#include "TextureManager.h"
#include <stdexcept>
#include "M_Assert.h"

TextureManager* TextureManager::ptrInstance = nullptr;


void TextureManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


TextureManager::~TextureManager()
{
	//delete all entities.
	for (std::map<std::string, Texture*>::iterator it = myMap.begin(); it != myMap.end(); it++)
	{
		delete it->second;
	}
}
Texture* TextureManager::privGet(std::string key)
{
	// test for non existing key
	std::string errmsg = "Key \'" + key + "\' does not exists";
	M_Assert(myMap[key] != nullptr, errmsg.c_str());
	return myMap[key];
}

void TextureManager::privLoad(std::string key, std::string path)
{
	//test for used key
	std::string errmsg = "Key \'" + key + "\' already exists";
	M_Assert(myMap[key] == nullptr, errmsg.c_str());
	myMap[key] = new Texture((DefaultPath + path).c_str());
}

void TextureManager::privLoad(std::string key, const unsigned char& red, const unsigned char& green, const unsigned char& blue)
{
	//test for used key
	std::string errmsg = "Key \'" + key + "\' already exists";
	M_Assert(myMap[key] == nullptr, errmsg.c_str());
	myMap[key] = new Texture(red, green, blue);
}