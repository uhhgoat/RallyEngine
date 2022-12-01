#include "ShaderManager.h"
#include <stdexcept>
#include "M_Assert.h"

ShaderManager* ShaderManager::ptrInstance = nullptr;


void ShaderManager::Delete()
{
	delete ptrInstance;
	ptrInstance = nullptr;
}


ShaderManager::~ShaderManager()
{
	//delete all entities.
	for (std::map<std::string, ShaderObject*>::iterator it = myMap.begin(); it != myMap.end(); it++)
	{
		delete it->second;
	}
}
ShaderObject* ShaderManager::privGet(std::string key)
{
	// test for non existing key
	std::string errmsg = "Key \'" + key + "\' does not exists";
	M_Assert(myMap[key] != nullptr, errmsg.c_str());
	return myMap[key];
}

void ShaderManager::privLoad(std::string key, std::string path)
{
	//test for used key
	std::string errmsg = "Key \'" + key + "\' already exists";
	M_Assert(myMap[key] == nullptr, errmsg.c_str());
	myMap[key] = new ShaderObject((DefaultPath + path).c_str());
}