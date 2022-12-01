#include "TerrainObjectManager.h"
#include <stdexcept>
#include "M_Assert.h"
#include "Terrain.h"

TerrainObjectManager* TerrainObjectManager::ptrInstance = nullptr;

TerrainObjectManager::TerrainObjectManager()
{
	
}

void TerrainObjectManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


TerrainObjectManager::~TerrainObjectManager()
{
	//delete all entities.
	for (std::map<std::string, Terrain*>::iterator it = myMap.begin(); it != myMap.end(); it++)
	{
		delete it->second;
	}
}
Terrain* TerrainObjectManager::privGet(std::string key)
{
	// test for non existing key
	std::string errmsg = "Key \'" + key + "\' does not exists";
	M_Assert(myMap[key] != nullptr, errmsg.c_str());
	return myMap[key];
}


void TerrainObjectManager::privLoad(std::string key, std::string path, float len, float maxheight, float ytrans, std::string textureKey, int RepeatU, int RepeatV)
{
	//test for used key
	std::string errmsg = "Key \'" + key + "\' already exists";
	M_Assert(myMap[key] == nullptr, errmsg.c_str());
	myMap[key] = new Terrain((DefaultPath + path).c_str(), len, maxheight, ytrans, TextureManager::Get(textureKey), RepeatU, RepeatV);
}
